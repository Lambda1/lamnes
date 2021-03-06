#ifndef __LAM_NES_HPP__
#define __LAM_NES_HPP__

#include <iostream>
#include <string>

#include "./Cartridge.hpp"
#include "./CPU6502.hpp"
#include "./PPU.hpp"
#include "./MainBuss.hpp"

namespace lamnes
{
	class LamNES
	{
	public:
		LamNES();
		~LamNES();

		void Init(const std::string &rom_path);

		void MainLoop();

	private:
		Cartridge m_cartridge;
		CPU6502 m_cpu6502;
		PPU m_ppu;
		MainBuss m_main_buss;
	};
}

#endif
