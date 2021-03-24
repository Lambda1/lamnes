#ifndef __PPU_HPP__
#define __PPU_HPP__

#include <iostream>
#include <vector>

#include "./VRAM.hpp"
#include "./DefType.hpp"
#include "./VirtualScreen.hpp"
#include "./Cartridge.hpp"

namespace lamnes
{
	class PPU
	{
	private:
		struct col
		{
			using type = unsigned char;
			type r, g, b;
			col(const int &red, const int &green, const int &blue):
				r(static_cast<type>(red)), g(static_cast<type>(green)), b(static_cast<type>(blue))
			{}
		};

		inline static constexpr size_t PALETTE_SIZE = 0x20;
		inline static constexpr size_t ONE_SPRITE_UNIT = 8;
		
		inline static constexpr size_t SPRITE_UNDER_RELATIVE_BYTE = 8;
		inline static constexpr size_t ONE_SPRITE_BYTE_UNIT = 16;

		inline static constexpr size_t SCREEN_WIDTH = 256;
		inline static constexpr size_t TILE_WIDTH = 32;

		inline static constexpr size_t ONE_LINE_CLOCK = 341;
		inline static constexpr size_t STORE_DATA_TIMING_LINE = 8;
		inline static constexpr size_t VISIBLE_SCANLINE_TIMING_LINE = 240;
		inline static constexpr size_t POST_RENDER_SCANLINE_TIMING_LINE = 241;
		inline static constexpr size_t VBLANK_TIMING_LINE = 260;
		inline static constexpr size_t PRE_RENDER_SCANLINE_TIMING_LINE = 261;

		inline static constexpr address PPUCTR = static_cast<address>(0x2000);
		inline static constexpr address PPUMASK = static_cast<address>(0x2001);
		inline static constexpr address PPUSTATUS = static_cast<address>(0x2002);
		inline static constexpr address OAMADDR = static_cast<address>(0x2003);
		inline static constexpr address OAMDATA = static_cast<address>(0x2004);
		inline static constexpr address PPUSCROLL = static_cast<address>(0x2005);
		inline static constexpr address PPUADDR = static_cast<address>(0x2006);
		inline static constexpr address PPUDATA = static_cast<address>(0x2007);

	public:
		PPU();
		~PPU();

		void Init(Cartridge *cartridge_ptr);
		void Step();

		void DebugPrint();

		void SetRegister(const address &addr, const type8 &data);

		void Reset();

	private:
		unsigned long long int m_cycles;
		unsigned long long int m_lines;

		type8 m_ppu_ctr;
		type8 m_ppu_mask;
		type8 m_ppu_status;
		address m_oam_addr;
		type8 m_oam_data;
		type8 m_ppu_scroll;
		address m_ppu_addr;

		bool m_ppu_scroll_write_check;
		bool m_ppu_addr_write_check;

		VRAM m_vram;
		std::vector<type8> m_palette;
		std::vector<col> m_palette_table;

		Cartridge *m_cartridge_ptr;

		VirtualScreen m_virtual_screen;
		size_t m_render_y;

		void PowerUp();
		
		void RenderEightLine();
		void RenderSpriteOneLine(const size_t &x, const size_t &y, const std::vector<char> &chr, const col &color);
		void ConvertSpriteOneLine(const type8 &layer1, const type8 &layer2, std::vector<char> &sprite_line);
	};
}

#endif
