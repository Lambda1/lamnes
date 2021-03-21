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

	// ‰Šú‰»ˆ—
	void MainBuss::Init(Cartridge* cartridge_ptr, CPU6502* cpu6502_ptr)
	{
		m_cartridge_ptr = cartridge_ptr;
		m_cpu6502_ptr = cpu6502_ptr;
	}
}