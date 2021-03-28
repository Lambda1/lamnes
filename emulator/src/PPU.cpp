#include "PPU.hpp"

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
		m_cartridge_ptr{ nullptr },
		m_virtual_screen{}, m_render_y{ 0 }
	{
		m_palette.resize(PALETTE_SIZE, 0);

		// パレットテーブル作成
		m_palette_table.emplace_back(col{ 84 , 84 , 84 });
		m_palette_table.emplace_back(col{ 0 , 30 , 116 });
		m_palette_table.emplace_back(col{ 8 , 16 , 144 });
		m_palette_table.emplace_back(col{ 48 , 0 , 136 });
		m_palette_table.emplace_back(col{ 68 , 0 , 100 });
		m_palette_table.emplace_back(col{ 92 , 0 , 48 });
		m_palette_table.emplace_back(col{ 84 , 4 , 0 });
		m_palette_table.emplace_back(col{ 60 , 24 , 0 });
		m_palette_table.emplace_back(col{ 32 , 42 , 0 });
		m_palette_table.emplace_back(col{ 8 , 58 , 0 });
		m_palette_table.emplace_back(col{ 0 , 64 , 0 });
		m_palette_table.emplace_back(col{ 0 , 60 , 0 });
		m_palette_table.emplace_back(col{ 0 , 50 , 60 });
		m_palette_table.emplace_back(col{ 0 , 0 , 0 });
		m_palette_table.emplace_back(col{ 152 , 150 , 152 });
		m_palette_table.emplace_back(col{ 8 , 76 , 196 });
		m_palette_table.emplace_back(col{ 48 , 50 , 236 });
		m_palette_table.emplace_back(col{ 92 , 30 , 228 });
		m_palette_table.emplace_back(col{ 136 , 20 , 176 });
		m_palette_table.emplace_back(col{ 160 , 20 , 100 });
		m_palette_table.emplace_back(col{ 152 , 34 , 32 });
		m_palette_table.emplace_back(col{ 120 , 60 , 0 });
		m_palette_table.emplace_back(col{ 84 , 90 , 0 });
		m_palette_table.emplace_back(col{ 40 , 114 , 0 });
		m_palette_table.emplace_back(col{ 8 , 124 , 0 });
		m_palette_table.emplace_back(col{ 0 , 118 , 40 });
		m_palette_table.emplace_back(col{ 0 , 102 , 120 });
		m_palette_table.emplace_back(col{ 0 , 0 , 0 });
		m_palette_table.emplace_back(col{ 236 , 238 , 236 });
		m_palette_table.emplace_back(col{ 76 , 154 , 236 });
		m_palette_table.emplace_back(col{ 120 , 124 , 236 });
		m_palette_table.emplace_back(col{ 176 , 98 , 236 });
		m_palette_table.emplace_back(col{ 228 , 84 , 236 });
		m_palette_table.emplace_back(col{ 236 , 88 , 180 });
		m_palette_table.emplace_back(col{ 236 , 106 , 100 });
		m_palette_table.emplace_back(col{ 212 , 136 , 32 });
		m_palette_table.emplace_back(col{ 160 , 170 , 0 });
		m_palette_table.emplace_back(col{ 116 , 196 , 0 });
		m_palette_table.emplace_back(col{ 76 , 208 , 32 });
		m_palette_table.emplace_back(col{ 56 , 204 , 108 });
		m_palette_table.emplace_back(col{ 56 , 180 , 204 });
		m_palette_table.emplace_back(col{ 60 , 60 , 60 });
		m_palette_table.emplace_back(col{ 236 , 238 , 236 });
		m_palette_table.emplace_back(col{ 168 , 204 , 236 });
		m_palette_table.emplace_back(col{ 188 , 188 , 236 });
		m_palette_table.emplace_back(col{ 212 , 178 , 236 });
		m_palette_table.emplace_back(col{ 236 , 174 , 236 });
		m_palette_table.emplace_back(col{ 236 , 174 , 212 });
		m_palette_table.emplace_back(col{ 236 , 180 , 176 });
		m_palette_table.emplace_back(col{ 228 , 196 , 144 });
		m_palette_table.emplace_back(col{ 204 , 210 , 120 });
		m_palette_table.emplace_back(col{ 180 , 222 , 120 });
		m_palette_table.emplace_back(col{ 168 , 226 , 144 });
		m_palette_table.emplace_back(col{ 152 , 226 , 180 });
		m_palette_table.emplace_back(col{ 160 , 214 , 228 });
		m_palette_table.emplace_back(col{ 160 , 162 , 160 });
	}
	PPU::~PPU()
	{
	}
	void PPU::Init(Cartridge* cartridge_ptr)
	{
		m_cartridge_ptr = cartridge_ptr;

		PowerUp();
		m_vram.Init();
		m_virtual_screen.Init();
	}

	// 処理実行
	void PPU::Step()
	{
		// 初めの[0]を除外するために，サイクル数をカウントする前にラインを加算．
		++m_cycles;
		if (m_cycles >= ONE_LINE_CLOCK)
		{
			m_cycles = 0;
			++m_lines;

			if (m_lines <= VISIBLE_SCANLINE_TIMING_LINE)
			{
				// 8ライン描画
				if ((m_lines % STORE_DATA_TIMING_LINE) == 0) { RenderEightLine(); }
			}
			else if (m_lines <= POST_RENDER_SCANLINE_TIMING_LINE)
			{
				// post-render
			}
			else if (m_lines <= VBLANK_TIMING_LINE)
			{
				// VBLANK
				m_ppu_status |= static_cast<type8>(0x80);
			}
			else if (m_lines <= PRE_RENDER_SCANLINE_TIMING_LINE)
			{
				// pre-render
			}
			else
			{
				// 1フレーム (341*262 = 89342)
				DebugPrint();
				m_virtual_screen.Output();
				m_virtual_screen.OutputPPM("./output.ppm");
				std::exit(EXIT_FAILURE);

				m_cycles = 0;
				m_lines = 0;
				m_ppu_status ^= 0x80; // reset vblank

				m_render_y = 0;
			}
		}
	}

	// デバッグ用メモリ内容表示
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
				// パレット
				auto adr_idx = (m_ppu_addr - static_cast<address>(0x3f00));
				m_palette[adr_idx] = data;
			}
			// インクリメント
			if ((m_ppu_ctr & PPUCTR) == PPUCTR) { m_ppu_addr += static_cast<type8>(0x20); }
			else { m_ppu_addr += static_cast<type8>(0x01); }
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

	// 8ライン描画
	void PPU::RenderEightLine()
	{
		std::vector<char> sprite_line(ONE_SPRITE_UNIT, 0);
		for (size_t i = 0; i < STORE_DATA_TIMING_LINE; ++i)
		{
			for (size_t j = 0; j < TILE_WIDTH; ++j)
			{
				// CHR ROMのアドレス取得
				auto y = m_render_y / ONE_SPRITE_UNIT;
				const address vram_addr = static_cast<address>(y * TILE_WIDTH + j);
				const address pattern_addr = static_cast<address>(m_vram.Read(vram_addr) * ONE_SPRITE_BYTE_UNIT);

				// レイヤの読み込み
				auto layer1 = m_cartridge_ptr->ReadCHRROM(static_cast<address>(pattern_addr + i));
				auto layer2 = m_cartridge_ptr->ReadCHRROM(static_cast<address>(pattern_addr + i + ONE_SPRITE_UNIT));
				// 1ライン分のスプライト生成
				ConvertSpriteOneLine(layer1, layer2, sprite_line);

				// 属性読み出し
				const address attribute_addr = 0x03C0 + vram_addr / (ONE_SPRITE_BYTE_UNIT * 2);
				const type8 attribute_val = m_vram.Read(attribute_addr);

				// 1ライン描画
				RenderSpriteOneLine(j, m_render_y, sprite_line, attribute_val);
			}
			++m_render_y;
		}
	}
	// 1スプライトの1ラインを描画
	void PPU::RenderSpriteOneLine(const size_t& x, const size_t& y, const std::vector<char> &chr, const type8 &attrib_val)
	{
		// タイルIDからパレットIDを算出
		const size_t tile_block_id = (((y / ONE_ATTRIBUTE_UNIT) % 2) << 1) | ((x / ONE_ATTRIBUTE_UNIT) % 2);
		const size_t palette_id = (attrib_val >> (tile_block_id * 2)) & 0x03;

		for (size_t j = 0; j < ONE_SPRITE_UNIT; ++j)
		{
			const size_t idx = palette_id * PALETTE_STRIDE + chr[j];
			const col color = m_palette_table[m_palette[idx]];
			
			m_virtual_screen.Render(x * ONE_SPRITE_UNIT + j, y, color.r ,color.g, color.b);
		}
	}

	// 1ライン分の2つのスプライトを1つのスプライトに変換
	// 00, 01, 10, 11の4種類
	void PPU::ConvertSpriteOneLine(const type8& layer1, const type8& layer2, std::vector<char> &sprite_line)
	{
		sprite_line[0] = ((layer2 >> 6) & 0x02) | ((layer1 & 0x80) >> 7);
		sprite_line[1] = ((layer2 >> 5) & 0x02) | ((layer1 & 0x40) >> 6);
		sprite_line[2] = ((layer2 >> 4) & 0x02) | ((layer1 & 0x20) >> 5);
		sprite_line[3] = ((layer2 >> 3) & 0x02) | ((layer1 & 0x10) >> 4);
		sprite_line[4] = ((layer2 >> 2) & 0x02) | ((layer1 & 0x08) >> 3);
		sprite_line[5] = ((layer2 >> 1) & 0x02) | ((layer1 & 0x04) >> 2);
		sprite_line[6] = ((layer2 >> 0) & 0x02) | ((layer1 & 0x02) >> 1);
		sprite_line[7] = ((layer2 << 1) & 0x02) | ((layer1 & 0x01) >> 0);
	}
}
