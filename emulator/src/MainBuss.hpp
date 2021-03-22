#ifndef __MAIN_BUSS_HPP__
#define __MAIN_BUSS_HPP__

#include <iostream>
#include <string>

#include "./Cartridge.hpp"
#include "./DefType.hpp"

namespace lamnes
{
	class CPU6502;
	class PPU;
	
	class MainBuss
	{
	private:

	public:
		MainBuss();
		~MainBuss();

		void Init(Cartridge *cartridge_ptr, CPU6502 *cpu6502_ptr, PPU *ppu_ptr);

		type8 Read(const address &addr);

	private:
		Cartridge* m_cartridge_ptr;
		CPU6502* m_cpu6502_ptr;
		PPU* m_ppu_ptr;
	};
}

#endif
