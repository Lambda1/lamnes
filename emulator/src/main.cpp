#include <iostream>

#include "Cartridge.hpp"
#include "CPU6502.hpp"

int main(int argc, char* argv[])
{
	// .nesファイル存在チェック
	if (argc < 2)
	{
		std::cerr << "./lamnes *.nes" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	lamnes::Cartridge cartridge{};
	cartridge.Init(argv[1]);

	lamnes::CPU6502 cpu6502{};
	cpu6502.Init();

	return 0;
}