#include <iostream>

#include "./LamNES.hpp"

int main(int argc, char* argv[])
{
	// .nesファイル存在チェック
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