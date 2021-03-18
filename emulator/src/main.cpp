#include <iostream>

#include "Cartridge.hpp"

int main(int argc, char* argv[])
{
	// .nesファイル存在チェック
	if (argc < 2)
	{
		std::cerr << "./lamnes *.nes" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	lamnes::Cartridge cartridge{};

	return 0;
}