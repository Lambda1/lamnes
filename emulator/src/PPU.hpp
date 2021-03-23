#ifndef __PPU_HPP__
#define __PPU_HPP__

#include <iostream>
#include <vector>

#include "./VRAM.hpp"
#include "./DefType.hpp"

namespace lamnes
{
	class PPU
	{
	private:
		inline static constexpr size_t PALETTE_SIZE = 0x20;

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

		void Init();
		void Step();

		void DebugPrint();

		void SetRegister(const address &addr, const type8 &data);

		void Reset();

	private:
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

		void PowerUp();
	};
}

#endif
