#include "Cartridge.hpp"

namespace lamnes
{
	Cartridge::Cartridge()
	{
		m_header.resize(HEADER_SIZE, 0);
	}

	// 初期化
	void Cartridge::Init(const std::string& nes_file_path)
	{
		auto rom_data = ReadRom(nes_file_path);
		ParseRom(rom_data);

		BuildSprite();
	}

	// PRG ROM取得
	type8 Cartridge::ReadPRGROM(const address& address)
	{
		return m_prg_rom[address];
	}
	// CHR ROM取得
	type8 Cartridge::ReadCHRROM(const address& address)
	{
		return m_chr_rom[address];
	}

	// 解析したROMを出力
	void Cartridge::DebugDump(const std::vector<type8>& data, const std::string& output_path)
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

	// CHR ROMをPPMに描画
	// NOTE: 処理効率がよくない
	void Cartridge::DebugDumpCHRROMToPPM(const std::string& file_path)
	{
		// サイズは固定(仮)
		const size_t sprite_num = m_sprite.size();
		const size_t img_size = 256;

		// 正方形領域に描画
		std::ofstream file(file_path, std::ios::out);
		file << "P3" << std::endl;
		file << static_cast<int>(img_size) << " " << static_cast<int>(img_size) << std::endl;
		file << static_cast<int>(255) << std::endl;

		// 仮想スクリーンに描画
		std::vector<type8> screen(img_size * img_size, 0);
		size_t screen_x = 0, screen_y = 0;
		for (const auto& sprite : m_sprite)
		{
			for (size_t i = 0; i < SPRITE_PIXEL_SIZE; ++i)
			{
				const size_t idx = screen_y * img_size + screen_x;
				for (size_t j = 0; j < SPRITE_PIXEL_SIZE; ++j)
				{
					screen[idx + (i * img_size + j)] = sprite.data[i * SPRITE_PIXEL_SIZE + j];
				}
			}
			screen_x = (screen_x + SPRITE_PIXEL_SIZE) % img_size;
			if (screen_x == 0) { screen_y += SPRITE_PIXEL_SIZE; }
		}

		// PPM出力
		for (size_t i = 0; i < img_size; ++i)
		{
			for (size_t j = 0; j < img_size; ++j)
			{
				const auto& val = screen[i * img_size + j];

				if (val == 0)
				{
					file << static_cast<int>(0x00) << " " << static_cast<int>(0x00) << " " << static_cast<int>(0x00) << std::endl;
				}
				else if(val == 1)
				{
					file << static_cast<int>(0xff) << " " << static_cast<int>(0x00) << " " << static_cast<int>(0x00) << std::endl;
				}
				else if (val == 2)
				{
					file << static_cast<int>(0x00) << " " << static_cast<int>(0xff) << " " << static_cast<int>(0x00) << std::endl;
				}
				else
				{
					file << static_cast<int>(0x00) << " " << static_cast<int>(0x00) << " " << static_cast<int>(0xff) << std::endl;
				}
			}
			file << std::endl;
		}
	}

	// ROMバイナリデータ取得
	std::vector<type8> Cartridge::ReadRom(const std::string& nes_file_path)
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
		std::vector<type8> data(size, 0);
		ines.read(data.data(), size);

		ines.close();

		return data;
	}

	// ROMデータの解析
	void Cartridge::ParseRom(std::vector<type8>& rom_data)
	{
		auto itr = rom_data.begin();

		// header
		std::copy(itr, itr + HEADER_SIZE, m_header.begin());
		itr += HEADER_SIZE;

		// trainer
		auto flags_6 = m_header[6];
		size_t trainer_size = TRAINER_UNIT * static_cast<size_t>(flags_6 & FLAGS6_TRAINER);
		m_trainer.resize(trainer_size, 0);
		std::copy(itr, itr + trainer_size, m_trainer.begin());
		itr += trainer_size;

		// PRG ROM
		size_t prg_rom_unit_size = static_cast<size_t>(m_header[4]);
		size_t prg_rom_size = PRG_ROM_UNIT * prg_rom_unit_size;
		m_prg_rom.resize(prg_rom_size, 0);
		std::copy(itr, itr + prg_rom_size, m_prg_rom.begin());
		itr += prg_rom_size;

		// CHR ROM
		size_t chr_rom_unit_size = static_cast<size_t>(m_header[5]);
		size_t chr_rom_size = CHR_ROM_UNIT * chr_rom_unit_size;
		m_chr_rom.resize(chr_rom_size, 0);
		std::copy(itr, itr + chr_rom_size, m_chr_rom.begin());
		itr += chr_rom_size;

		// PlayChoice INST-ROM
		auto flags_7 = m_header[7];
		size_t inst_rom_size = INST_ROM_UNIT * static_cast<size_t>(flags_7 & FLAGS7_PLAYCHOICE);
		m_inst_rom.resize(inst_rom_size, 0);
		std::copy(itr, itr + inst_rom_size, m_inst_rom.begin());
		itr += inst_rom_size;

		// PlayChoice PROM
		/* 未実装 */
	}

	// スプライトを生成
	void Cartridge::BuildSprite()
	{
		const auto sprite_num = m_chr_rom.size() / SPRITE_BYTE;
		m_sprite.resize(sprite_num, {});

		size_t idx = 0;
		for (auto& sprite : m_sprite)
		{
			for (size_t i = 0; i < SPRITE_PIXEL_SIZE; ++i)
			{
				const auto layer1 = m_chr_rom[idx + (i + 0)];
				const auto layer2 = m_chr_rom[idx + (i + SPRITE_LINE_STRIDE)];
				for (size_t j = 0; j < SPRITE_PIXEL_SIZE; ++j)
				{
					sprite.data[i * SPRITE_PIXEL_SIZE + (SPRITE_PIXEL_SIZE - 1 - j)] = ((layer1 >> j) & 0x01) | (((layer2 >> j) & 0x01) << 0x01);
				}
			}
			idx += SPRITE_BYTE;
		}
	}
}
