#include <iostream>

#include "./LamNES.hpp"

int main(int argc, char* argv[])
{
	// .nes�t�@�C�����݃`�F�b�N
	if (argc < 2)
	{
		std::cerr << "./lamnes *.nes" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	lamnes::LamNES nes{};
	nes.Init(argv[1]);

	nes.MainLoop();

	return 0;
}