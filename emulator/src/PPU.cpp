#include "PPU.hpp"

namespace lamnes
{
	PPU::PPU():
		m_ppu_ctr{0}, m_ppu_mask{0}, m_ppu_status{0},
		m_oam_addr{0}, m_oam_data{0},
		m_ppu_scroll{0}, m_ppu_addr{0},
		m_ppu_scroll_write_check(false),
		m_ppu_addr_write_check(false),
		m_vram{}
	{
		m_palette.resize(PALETTE_SIZE, 0);
	}
	PPU::~PPU()
	{
	}
	void PPU::Init()
	{
		PowerUp();
		m_vram.Init();
	}

	// �������s
	void PPU::Step()
	{
	}

	// �f�o�b�O�p���������e�\��
	void PPU::DebugPrint()
	{
#if _DEBUG
		std::cout << "PPUCTR   : " << std::hex << static_cast<int>(m_ppu_ctr & 0xff) << std::endl;
		std::cout << "PPUMASK  : " << std::hex << static_cast<int>(m_ppu_mask & 0xff) << std::endl;
		std::cout << "PPUSTATUS: " << std::hex << static_cast<int>(m_ppu_status & 0xff) << std::endl;
		std::cout << "OAMADDR  : " << std::hex << static_cast<int>(m_oam_addr & 0xffff) << std::endl;
		std::cout << "OAMDATA  : " << std::hex << static_cast<int>(m_oam_data & 0xff) << std::endl;
		std::cout << "PPUSCROLL: " << std::hex << static_cast<int>(m_ppu_scroll & 0xff) << std::endl;
		std::cout << "PPUADDR  : " << std::hex << static_cast<int>(m_ppu_addr & 0xffff) << std::endl;
#endif
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
				m_ppu_addr = (static_cast<address>(data) << 8);
			}
			else
			{
				m_ppu_addr |= static_cast<address>(data);
			}
			m_ppu_addr_write_check = !m_ppu_addr_write_check;
			break;
		case PPUDATA:
			if (m_ppu_addr < 0x3f00)
			{
				std::exit(EXIT_FAILURE);
			}
			else if (m_ppu_addr < 0x3f20)
			{
				// �p���b�g
				auto adr_idx = (m_ppu_addr - static_cast<address>(0x3f00));
				m_palette[adr_idx] = data;
				// �C���N�������g
				if ((m_ppu_ctr & PPUCTR) == PPUCTR) { m_ppu_addr += static_cast<type8>(0x20); }
				else { m_ppu_addr += static_cast<type8>(0x01); }
			}
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
