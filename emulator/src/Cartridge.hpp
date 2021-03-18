#ifndef __CARTRIDGE_HPP__
#define __CARTRIDGE_HPP__

#include <vector>
#include <string>

namespace lamnes
{
	class Cartridge
	{
		using type = unsigned char;
	public:
		Cartridge();

		bool Init(const std::string &nes_file_path);
	private:
		std::vector<type> m_header;
	};
}

#endif
