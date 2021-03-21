#ifndef __CPU_6502_HPP__
#define __CPU_6502_HPP__

#include <iostream>
#include <vector>

#include "./DefStatusRegister.hpp"
#include "./DefType.hpp"

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

	private:
		type8 m_accumulator;
		type8 m_idx_reg_x, m_idx_reg_y;
		type8 m_stack_ptr;
		type8 m_status_reg;
		address m_pc;

		MainBuss* m_main_buss_ptr;

		void PowerUp();

		address Fetch(const address &addr);
	};
}

#endif
