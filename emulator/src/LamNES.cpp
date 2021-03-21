#include "LamNES.hpp"

namespace lamnes
{
	LamNES::LamNES():
		m_cartridge{},
		m_cpu6502{}
	{
	}
	LamNES::~LamNES()
	{
	}

	// 初期化処理
	void LamNES::Init(const std::string& rom_path)
	{
		m_cartridge.Init(rom_path);
		m_cpu6502.Init();
	}
}
