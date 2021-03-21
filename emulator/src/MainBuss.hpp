#ifndef __MAIN_BUSS_HPP__
#define __MAIN_BUSS_HPP__

#include <iostream>
#include <string>

#include "./Cartridge.hpp"
#include "./CPU6502.hpp"

namespace lamnes
{
	class MainBuss
	{
	public:
		MainBuss();
		~MainBuss();

		void Init();
	private:
	};
}

#endif
