#include <iostream>

#include "Cartridge.hpp"

int main(int argc, char* argv[])
{
	// .nes�t�@�C�����݃`�F�b�N
	if (argc < 2)
	{
		std::cerr << "./lamnes *.nes" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	lamnes::Cartridge cartridge{};

	return 0;
}