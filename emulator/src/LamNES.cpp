#include "LamNES.hpp"

namespace lamnes
{
	LamNES::LamNES():
		m_cartridge{},
		m_cpu6502{},
		m_main_buss{}
	{
	}
	LamNES::~LamNES()
	{
	}

	// ‰Šú‰»ˆ—
	void LamNES::Init(const std::string& rom_path)
	{
		m_main_buss.Init(&m_cartridge, &m_cpu6502);
		
		m_cartridge.Init(rom_path);
		m_cpu6502.Init(&m_main_buss);
	}
}
