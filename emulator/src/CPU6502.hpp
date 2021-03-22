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

		void DebugPrint();

	private:
		type8 m_accumulator;
		type8 m_idx_reg_x, m_idx_reg_y;
		type8 m_stack_ptr_value;
		type8 m_status_reg;
		address m_pc;

		unsigned long long int m_cycles;

		MainBuss* m_main_buss_ptr;

		void PowerUp();

		type8 Fetch(const address &addr);
		Addressing Decode(const type8 &op);
		void Execute(const Addressing &mode, const type8 &op);

		void ExecuteImplied(const type8& op);
		void ExecuteAccumulator(const type8& op);
		void ExecuteImmediate(const type8& op);
		void ExecuteZeropage(const type8& op);
		void ExecuteZeropageX(const type8& op);
		void ExecuteZeropageY(const type8& op);
		void ExecuteRelative(const type8& op);
		void ExecuteAbsolute(const type8& op);
		void ExecuteAbsoluteX(const type8& op);
		void ExecuteAbsoluteY(const type8& op);
		void ExecuteIndirect(const type8& op);
		void ExecuteIndirectX(const type8& op);
		void ExecuteIndirectY(const type8& op);

		address GetAddressFromPC();

	};
}

#endif
