#include "./MainBuss.hpp"

#include "./CPU6502.hpp"
#include "./PPU.hpp"

namespace lamnes
{
	MainBuss::MainBuss():
		m_cartridge_ptr{nullptr},
		m_cpu6502_ptr{nullptr},
		m_ppu_ptr{nullptr}
	{
		m_wram.resize(0x0800, 0);
	}
	MainBuss::~MainBuss()
	{
	}

	// 初期化処理
	void MainBuss::Init(Cartridge* cartridge_ptr, CPU6502* cpu6502_ptr, PPU *ppu_ptr)
	{
		m_cartridge_ptr = cartridge_ptr;
		m_cpu6502_ptr = cpu6502_ptr;
		m_ppu_ptr = ppu_ptr;
	}

	// データ読み込み
	type8 MainBuss::Read(const address& addr)
	{
		type8 data = 0;
		
		if (addr < static_cast<address>(0x0800))
		{
			// WRAM
			data = m_wram[addr];
		}
		else if (addr < static_cast<address>(0x2000))
		{
			// 0x0000-0x07ff MIRROR
			std::cerr << "MIR" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x2007))
		{
			// I/O PPU
			data = m_ppu_ptr->Read(addr);
		}
		else if (addr < static_cast<address>(0x4000))
		{
			// 0x2000-0x2007 MIRROR
			std::cerr << "MIR" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x401F))
		{
			// I/O APU
			std::cerr << "IO APU" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x6000))
		{
			// 拡張RAM
			std::cerr << "ex ram" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x8000))
		{
			// バッテリーバックアップRAM
			std::cerr << "back ram" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0xC000))
		{
			// PRG ROM LOW
			address conv_addr = (addr - static_cast<address>(0x8000));
			data = m_cartridge_ptr->ReadPRGROM(conv_addr);
		}
		else
		{
			// PRG ROM HIGH
			address conv_addr = (addr - static_cast<address>(0x8000));
			data = m_cartridge_ptr->ReadPRGROM(conv_addr);
		}
		
		return data;
	}
	// データ書き込み
	void MainBuss::Write(const address& addr, const type8& data)
	{
		if (addr < static_cast<address>(0x0800))
		{
			// WRAM
			std::cerr << "WRAM" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x2000))
		{
			// 0x0000-0x07ff MIRROR
			std::cerr << "MIR" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x2008))
		{
			// I/O PPU
			m_ppu_ptr->SetRegister(addr, data);
		}
		else if (addr < static_cast<address>(0x4000))
		{
			// 0x2000-0x2007 MIRROR
			std::cerr << "MIR" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x401F))
		{
			// I/O APU
			std::cerr << "IO APU" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x6000))
		{
			// 拡張RAM
			std::cerr << "ex ram" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0x8000))
		{
			// バッテリーバックアップRAM
			std::cerr << "back ram" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (addr < static_cast<address>(0xC000))
		{
			// PRG ROM LOW
			std::cerr << "Write: PRG ROM LOW" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else
		{
			// PRG ROM HIGH
			std::cerr << "Write: PRG ROM HIGH" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}