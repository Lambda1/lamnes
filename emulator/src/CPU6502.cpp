#include "CPU6502.hpp"

namespace lamnes
{
	CPU6502::CPU6502() :
		m_accumulator{ 0 },
		m_idx_reg_x{ 0 }, m_idx_reg_y{ 0 },
		m_stack_ptr{ 0 },
		m_status_reg{ 0 },
		m_pc{ 0 }
	{
		m_memory.resize(0xffff, 0);
	}

	CPU6502::~CPU6502()
	{
	}

	void CPU6502::Init()
	{
		PowerUp();
	}

	// ìdåπìäì¸èàóù
	void CPU6502::PowerUp()
	{
		m_pc = static_cast<type16>(0x34);
		m_accumulator = static_cast<type8>(0x00);
		m_idx_reg_x = static_cast<type8>(0x00);
		m_idx_reg_y = static_cast<type8>(0x00);
		m_stack_ptr = static_cast<type8>(0xfd);

		// frame irq enable
		m_memory[0x4017] = static_cast<type16>(0x00);
		// all channels disable
		m_memory[0x4015] = static_cast<type16>(0x00);

		for (size_t i = 0x4000; i <= 0x400f; ++i) { m_memory[i] = static_cast<type16>(0x00); }
		for (size_t i = 0x4010; i <= 0x4013; ++i) { m_memory[i] = static_cast<type16>(0x00); }
	}
}
