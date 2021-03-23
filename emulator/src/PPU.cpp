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

	// 処理実行
	void PPU::Step()
	{
	}

	// デバッグ用メモリ内容表示
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

	// レジスタ設定
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
			// 未完成
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
			// 1回目: 上位8bit, 2回目: 下位8bit
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
				// パレット
				auto adr_idx = (m_ppu_addr - static_cast<address>(0x3f00));
				m_palette[adr_idx] = data;
				// インクリメント
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

	// リセット処理
	void PPU::Reset()
	{
		m_ppu_ctr = 0;
		m_ppu_mask = 0;
		m_ppu_status = 0; // randomらしい
		m_ppu_scroll = 0;
	}

	// 電源投入時処理
	void PPU::PowerUp()
	{
		m_ppu_ctr = 0;
		m_ppu_mask = 0;
		m_ppu_status = 0; // randomらしい
		m_oam_addr = 0;
		m_ppu_scroll = 0;
		m_ppu_addr = 0;
	}
}
