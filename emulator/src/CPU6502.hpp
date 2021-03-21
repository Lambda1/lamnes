#ifndef __CPU_6502_HPP__
#define __CPU_6502_HPP__

#include <iostream>
#include <vector>

#include "./DefType.hpp"
#include "./DefStatusRegister.hpp"
#include "./DefOpcode.hpp"
#include "./DefAddressing.hpp"

namespace lamnes
{
	class MainBuss;
	
	class CPU6502
	{
	private:

	public:
		CPU6502();
		~CPU6502();

		void Init(MainBuss *main_buss);
		
		void Reset();
		void Step();

	private:
		type8 m_accumulator;
		type8 m_idx_reg_x, m_idx_reg_y;
		type8 m_stack_ptr;
		type8 m_status_reg;
		address m_pc;

		unsigned long long int m_cycles;

		MainBuss* m_main_buss_ptr;

		void PowerUp();

		type8 Fetch(const address &addr);
		Addressing Decode(const type8 &op);

	};
}

#endif
