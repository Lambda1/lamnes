#ifndef __CARTRIDGE_HPP__
#define __CARTRIDGE_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

namespace lamnes
{
	class Cartridge
	{
	private:
		using type = char;

		// iNES file format(Byte)
		inline static constexpr size_t HEADER_SIZE = 16;
		inline static constexpr size_t TRAINER_UNIT = 512;
		inline static constexpr size_t PRG_ROM_UNIT = 16384;
		inline static constexpr size_t CHR_ROM_UNIT = 8192;
		inline static constexpr size_t INST_ROM_UNIT = 8192;
		inline static constexpr size_t P_ROM_UNIT = 16;

		// Flags6
		inline static constexpr type FLAGS6_MIRRORING = static_cast<type>(0x01);
		inline static constexpr type FLAGS6_BATTERY = static_cast<type>(0x02);
		inline static constexpr type FLAGS6_TRAINER = static_cast<type>(0x04);
		inline static constexpr type FLAGS6_IGNORE_MIRRORING = static_cast<type>(0x08);
		inline static constexpr type FLAGS6_MAPPER = static_cast<type>(0xF0);
		
		// Flags7
		inline static constexpr type FLAGS7_VS = static_cast<type>(0x01);
		inline static constexpr type FLAGS7_PLAYCHOICE = static_cast<type>(0x02);
		inline static constexpr type FLAGS7_NES2_0 = static_cast<type>(0x0C);
		inline static constexpr type FLAGS7_MAPPER = static_cast<type>(0xF0);

	public:
		Cartridge();

		void Init(const std::string &nes_file_path);
		
		void DebugDump(const std::vector<type> &data, const std::string &output_path);
	private:
		std::vector<type> m_header;

		std::vector<type> m_trainer;
		std::vector<type> m_prg_rom;
		std::vector<type> m_chr_rom;
		std::vector<type> m_inst_rom;
		std::vector<type> m_prom_rom;

		std::vector<type> ReadRom(const std::string &nes_file_path);
		void ParseRom(std::vector<type> &rom_data);
	};
}

#endif
