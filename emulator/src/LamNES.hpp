#ifndef __LAM_NES_HPP__
#define __LAM_NES_HPP__

#include <iostream>
#include <string>

#include "./Cartridge.hpp"
#include "./CPU6502.hpp"

namespace lamnes
{
	class LamNES
	{
	public:
		LamNES();
		~LamNES();

		void Init(const std::string &rom_path);

	private:
		Cartridge m_cartridge;
		CPU6502 m_cpu6502;
	};
}

#endif
