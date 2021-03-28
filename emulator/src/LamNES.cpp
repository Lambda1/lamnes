#include "LamNES.hpp"

namespace lamnes
{
	LamNES::LamNES():
		m_cartridge{},
		m_cpu6502{},
		m_ppu{},
		m_main_buss{}
	{
	}
	LamNES::~LamNES()
	{
	}

	// ‰Šú‰»ˆ—
	void LamNES::Init(const std::string& rom_path)
	{
		m_main_buss.Init(&m_cartridge, &m_cpu6502, &m_ppu);
		
		m_cartridge.Init(rom_path);
		m_cpu6502.Init(&m_main_buss);
		m_ppu.Init(&m_cartridge);
	}

	// ƒƒCƒ“ˆ—
	void LamNES::MainLoop()
	{
		m_cartridge.DebugDumpCHRROMToPPM("./chr_rom_data.ppm");

		bool is_end = false;
		while (!is_end)
		{
#if _DEBUG
			m_cpu6502.DebugPrint();
			//m_ppu.DebugPrint();
#endif
			m_cpu6502.Step();
			m_ppu.Step();
			m_ppu.Step();
			m_ppu.Step();
		}
	}
}
