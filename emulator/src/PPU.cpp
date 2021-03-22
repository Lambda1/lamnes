#include "PPU.hpp"

namespace lamnes
{
	PPU::PPU():
		m_ppu_ctr{0}, m_ppu_mask{0}, m_ppu_status{0},
		m_oam_addr{0}, m_oam_data{0},
		m_ppu_scroll{0}, m_ppu_addr{0}, m_ppu_data{0}
	{
	}
	PPU::~PPU()
	{
	}
	void PPU::Init()
	{
	}
}
