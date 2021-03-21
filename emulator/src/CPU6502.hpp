#ifndef __CPU_6502_HPP__
#define __CPU_6502_HPP__

#include <iostream>
#include <vector>

namespace lamnes
{
	class CPU6502
	{
	private:
		using type8 = char;
		using type16 = char16_t;

	public:
		CPU6502();
		~CPU6502();

		void Init();

	private:
		type8 m_accumulator;
		type8 m_idx_reg_x, m_idx_reg_y;
		type8 m_stack_ptr;
		type8 m_status_reg;
		type16 m_pc;

		std::vector<type16> m_memory;

		void PowerUp();
	};
}

#endif
