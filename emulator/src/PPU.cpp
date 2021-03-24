#include "PPU.hpp"

#include "./MainBuss.hpp"

namespace lamnes
{
	PPU::PPU() :
		m_cycles{ 0 }, m_lines{ 0 },
		m_ppu_ctr{ 0 }, m_ppu_mask{ 0 }, m_ppu_status{ 0 },
		m_oam_addr{ 0 }, m_oam_data{ 0 },
		m_ppu_scroll{ 0 }, m_ppu_addr{ 0 },
		m_ppu_scroll_write_check(false),
		m_ppu_addr_write_check(false),
		m_vram{},
		m_main_buss_ptr{ nullptr },
		m_virtual_screen{}
	{
		m_palette.resize(PALETTE_SIZE, 0);

		// �p���b�g�e�[�u���쐬
		m_palette_table.push_back({84 , 84 , 84 });
		m_palette_table.push_back({0  , 36 , 116});
		m_palette_table.push_back({8  , 16 , 144});
		m_palette_table.push_back({48 , 0  , 136});
		m_palette_table.push_back({68 , 0  , 100});
		m_palette_table.push_back({92 , 0  , 48 });
		m_palette_table.push_back({84 , 4  , 0  });
		m_palette_table.push_back({60 , 24 , 0  });
		m_palette_table.push_back({32 , 42 , 0  });
		m_palette_table.push_back({32 , 42 , 0  });
	}
	PPU::~PPU()
	{
	}
	void PPU::Init(MainBuss* main_buss_ptr)
	{
		m_main_buss_ptr = main_buss_ptr;

		PowerUp();
		m_vram.Init();
		m_virtual_screen.Init();
	}

	// �������s
	void PPU::Step()
	{
		++m_cycles;

		// 1���C��
		if ((m_cycles % ONE_LINE_CLOCK) == 0)
		{
			++m_lines;
		}

		if (m_lines < VISIBLE_SCANLINE_TIMING_LINE)
		{
			// 8���C���`��
			if ((m_lines % STORE_DATA_TIMING_LINE) == 0)
			{
			}
		}
		else if (m_lines < POST_RENDER_SCANLINE_TIMING_LINE)
		{
			// post-render
		}
		else if (m_lines < VBLANK_TIMING_LINE)
		{
			// VBLANK
			m_ppu_status |= static_cast<type8>(0x80);
		}
		else if (m_lines < PRE_RENDER_SCANLINE_TIMING_LINE)
		{
			// pre-render
		}
		else
		{
			// 1�t���[�� (341*262 = 89342)
			DebugPrint();
			std::exit(EXIT_FAILURE);

			m_cycles = 0;
			m_lines = 0;
			m_ppu_status ^= 0x80; // reset vblank
		}
	}

	// �f�o�b�O�p���������e�\��
	void PPU::DebugPrint()
	{
		std::cerr << "PPU CYCL : " << std::dec << static_cast<int>(m_cycles) << std::endl;
		std::cerr << "PPU LINES: " << std::dec << static_cast<int>(m_lines) << std::endl;
		std::cerr << "PPUCTR   : " << std::hex << static_cast<int>(m_ppu_ctr & 0xff) << std::endl;
		std::cerr << "PPUMASK  : " << std::hex << static_cast<int>(m_ppu_mask & 0xff) << std::endl;
		std::cerr << "PPUSTATUS: " << std::hex << static_cast<int>(m_ppu_status & 0xff) << std::endl;
		std::cerr << "OAMADDR  : " << std::hex << static_cast<int>(m_oam_addr & 0xffff) << std::endl;
		std::cerr << "OAMDATA  : " << std::hex << static_cast<int>(m_oam_data & 0xff) << std::endl;
		std::cerr << "PPUSCROLL: " << std::hex << static_cast<int>(m_ppu_scroll & 0xff) << std::endl;
		std::cerr << "PPUADDR  : " << std::hex << static_cast<int>(m_ppu_addr & 0xffff) << std::endl;
	}

	// ���W�X�^�ݒ�
	void PPU::SetRegister(const address& addr, const type8& data)
	{
		switch (addr)
		{
		case PPUCTR:
			m_ppu_ctr = data;
			break;
		case PPUMASK:
			m_ppu_mask = data;
			break;
		case OAMADDR:
			std::exit(EXIT_FAILURE);
			break;
		case OAMDATA:
			std::exit(EXIT_FAILURE);
			break;
		case PPUSCROLL:
			// ������
			if (!m_ppu_scroll_write_check)
			{
				// horizontal
				m_ppu_scroll = data;
			}
			else
			{
				// vertical
				m_ppu_scroll = data;
			}
			m_ppu_scroll_write_check = !m_ppu_scroll_write_check;
			break;
		case PPUADDR:
			// 1���: ���8bit, 2���: ����8bit
			if (!m_ppu_addr_write_check)
			{
				m_ppu_addr = ((static_cast<address>(data) & 0xff) << 8);
			}
			else
			{
				m_ppu_addr |= static_cast<address>((static_cast<address>(data) & 0xff));
			}
			m_ppu_addr_write_check = !m_ppu_addr_write_check;
			break;
		case PPUDATA:
			if (m_ppu_addr < 0x3f00)
			{
				// VRAM
				auto adr_idx = (m_ppu_addr - static_cast<address>(0x2000));
				m_vram.Write(adr_idx, data);
			}
			else if (m_ppu_addr < 0x3f20)
			{
				// �p���b�g
				auto adr_idx = (m_ppu_addr - static_cast<address>(0x3f00));
				m_palette[adr_idx] = data;
			}
			// �C���N�������g
			if ((m_ppu_ctr & PPUCTR) == PPUCTR) { m_ppu_addr += static_cast<type8>(0x20); }
			else { m_ppu_addr += static_cast<type8>(0x01); }
			break;
		default:
			std::cerr << "ERROR: PPU set invalid register." << std::endl;
			std::exit(EXIT_FAILURE);
			break;
		}
	}

	// ���Z�b�g����
	void PPU::Reset()
	{
		m_ppu_ctr = 0;
		m_ppu_mask = 0;
		m_ppu_status = 0; // random�炵��
		m_ppu_scroll = 0;
	}

	// �d������������
	void PPU::PowerUp()
	{
		m_ppu_ctr = 0;
		m_ppu_mask = 0;
		m_ppu_status = 0; // random�炵��
		m_oam_addr = 0;
		m_ppu_scroll = 0;
		m_ppu_addr = 0;
	}
	}
