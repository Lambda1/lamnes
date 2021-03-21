#ifndef __MAIN_BUSS_HPP__
#define __MAIN_BUSS_HPP__

#include <iostream>
#include <string>

#include "./Cartridge.hpp"

namespace lamnes
{
	class CPU6502;
	
	class MainBuss
	{
	public:
		MainBuss();
		~MainBuss();

		void Init(Cartridge *cartridge_ptr, CPU6502 *cpu6502_ptr);
	private:
		Cartridge* m_cartridge_ptr;
		CPU6502* m_cpu6502_ptr;
	};
}

#endif
