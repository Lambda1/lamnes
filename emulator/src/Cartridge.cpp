#include "Cartridge.hpp"

namespace lamnes
{
	Cartridge::Cartridge()
	{
		m_header.resize(HEADER_SIZE, 0);
	}

	// 初期化
	bool Cartridge::Init(const std::string& nes_file_path)
	{
		auto rom_data = ReadRom(nes_file_path);
		ParseRom(rom_data);

		DebugDump(m_header, "../roms/test.nes");
		DebugDump(m_prg_rom,"../roms/test.nes");
		DebugDump(m_chr_rom,"../roms/test.nes");

		return true;
	}

	// 解析したROMを出力
	void Cartridge::DebugDump(const std::vector<type> &data, const std::string &output_path)
	{
		std::ofstream file(output_path, std::ios::out | std::ios::app | std::ios::binary);
		if (!file)
		{
			std::cerr << output_path << " does not exist." << std::endl;
			std::exit(EXIT_FAILURE);
		}

		for (auto dt : data) { file << dt; }

		file.close();
	}

	// ROMバイナリデータ取得
	std::vector<Cartridge::type> Cartridge::ReadRom(const std::string& nes_file_path)
	{
		std::ifstream ines(nes_file_path, std::ios::in | std::ios::binary);
		if (!ines)
		{
			std::cerr << nes_file_path << " does not exist." << std::endl;
			std::exit(EXIT_FAILURE);
		}

		// ファイルサイズ取得
		ines.seekg(0, std::ios::end);
		auto size = ines.tellg();
		ines.seekg(0, std::ios::beg);

		// 全読み込み
		std::vector<type> data(size, 0);
		ines.read(data.data(), size);

		ines.close();

		return data;
	}

	// ROMデータの解析
	void Cartridge::ParseRom(std::vector<type>& rom_data)
	{
		auto itr = rom_data.begin();

		// header
		std::copy(itr, itr+HEADER_SIZE, m_header.begin());
		itr += HEADER_SIZE;

		// trainer
		auto flags_6 = m_header[6];
		size_t trainer_size = TRAINER_UNIT * static_cast<size_t>(flags_6 & FLAGS6_TRAINER);
		m_trainer.resize(trainer_size, 0);
		std::copy(itr, itr+trainer_size, m_trainer.begin());
		itr += trainer_size;

		// PRG ROM
		size_t prg_rom_unit_size = static_cast<size_t>(m_header[4]);
		size_t prg_rom_size = PRG_ROM_UNIT * prg_rom_unit_size;
		m_prg_rom.resize(prg_rom_size, 0);
		std::copy(itr, itr+prg_rom_size, m_prg_rom.begin());
		itr += prg_rom_size;

		// CHR ROM
		size_t chr_rom_unit_size = static_cast<size_t>(m_header[5]);
		size_t chr_rom_size = CHR_ROM_UNIT * chr_rom_unit_size;
		m_chr_rom.resize(chr_rom_size, 0);
		std::copy(itr, itr+chr_rom_size, m_chr_rom.begin());
		itr += chr_rom_size;

		// PlayChoice INST-ROM
		auto flags_7 = m_header[7];
		size_t inst_rom_size = INST_ROM_UNIT * static_cast<size_t>(flags_7 & FLAGS7_PLAYCHOICE);
		m_inst_rom.resize(inst_rom_size, 0);
		std::copy(itr, itr+inst_rom_size, m_inst_rom.begin());
		itr += inst_rom_size;

		// PlayChoice PROM
		/* 未実装 */
	}

}
