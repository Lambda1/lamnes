#include "./MainBuss.hpp"

#include "./CPU6502.hpp"

namespace lamnes
{
	MainBuss::MainBuss():
		m_cartridge_ptr{nullptr},
		m_cpu6502_ptr{nullptr}
	{
	}
	MainBuss::~MainBuss()
	{
	}

	// ����������
	void MainBuss::Init(Cartridge* cartridge_ptr, CPU6502* cpu6502_ptr)
	{
		m_cartridge_ptr = cartridge_ptr;
		m_cpu6502_ptr = cpu6502_ptr;
	}

	// �f�[�^�ǂݍ���
	type8 MainBuss::Read(const address& addr)
	{
		type8 data = 0;
		
		if (addr < static_cast<address>(0x0800))
		{
			// WRAM
		}
		else if (addr < static_cast<address>(0x2000))
		{
			// 0x0000-0x07ff MIRROR
		}
		else if (addr < static_cast<address>(0x2007))
		{
			// I/O PPU
		}
		else if (addr < static_cast<address>(0x4000))
		{
			// 0x2000-0x2007 MIRROR
		}
		else if (addr < static_cast<address>(0x401F))
		{
			// I/O APU
		}
		else if (addr < static_cast<address>(0x6000))
		{
			// �g��RAM
		}
		else if (addr < static_cast<address>(0x8000))
		{
			// �o�b�e���[�o�b�N�A�b�vRAM
		}
		else if (addr < static_cast<address>(0xC000))
		{
			// PRG ROM LOW
			address conv_addr = (addr - static_cast<address>(0x8000));
			data = m_cartridge_ptr->GetPRGROM(conv_addr);
		}
		else
		{
			// PRG ROM HIGH
			address conv_addr = (addr - static_cast<address>(0x8000));
			data = m_cartridge_ptr->GetPRGROM(conv_addr);
		}
		
		return data;
	}
}