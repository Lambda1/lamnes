#ifndef __PPU_HPP__
#define __PPU_HPP__

#include "./DefType.hpp"

namespace lamnes
{
	class PPU
	{
	public:
		PPU();
		~PPU();

		void Init();

	private:
		type8 m_ppu_ctr;
		type8 m_ppu_mask;
		type8 m_ppu_status;
		type8 m_oam_addr;
		type8 m_oam_data;
		type8 m_ppu_scroll;
		type8 m_ppu_addr;
		type8 m_ppu_data;
	};
}

#endif
