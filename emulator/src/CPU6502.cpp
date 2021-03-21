#include "./CPU6502.hpp"

#include "./MainBuss.hpp"

namespace lamnes
{
	/* public */

	CPU6502::CPU6502() :
		m_accumulator{ 0 },
		m_idx_reg_x{ 0 }, m_idx_reg_y{ 0 },
		m_stack_ptr{ 0 },
		m_status_reg{ 0 },
		m_pc{ 0 },
		m_cycles{0},
		m_main_buss_ptr{nullptr}
	{
	}

	CPU6502::~CPU6502()
	{
	}

	// 初期化処理
	void CPU6502::Init(MainBuss* main_buss)
	{
		m_main_buss_ptr = main_buss;
		if (!m_main_buss_ptr)
		{
			std::cerr << "CPU6502: MainBuss is nullptr." << std::endl;
			std::exit(EXIT_FAILURE);
		}

		PowerUp();
		Reset();
	}

	// リセット処理
	void CPU6502::Reset()
	{
		m_status_reg = Status::I; // 割り込み禁止
		m_pc = Fetch(0xfffc) | (Fetch(0xfffd) << 8);
	}
	// 処理実行
	void CPU6502::Step()
	{
#if _DEBUG
		std::cout << "\n" << "CYCLE: " << m_cycles << std::endl;
		std::cout << "PGCNT: " << std::hex << m_pc << std::endl;
		std::cout << "STATUS: " << std::hex << static_cast<int>(m_status_reg) << std::endl;
#endif
		type8 op = Fetch(m_pc++);
		Addressing mode = Decode(op);
		Execute(mode, op);
	}

	/* private */

	// 電源投入処理
	void CPU6502::PowerUp()
	{
		m_pc = static_cast<type16>(0x34);
		m_accumulator = static_cast<type8>(0x00);
		m_idx_reg_x = static_cast<type8>(0x00);
		m_idx_reg_y = static_cast<type8>(0x00);
		m_stack_ptr = static_cast<type8>(0xfd);

		// frame irq enable
		// 未実装
		
		// all channels disable
		// 未実装

		// 0x4000-0x400f = 0x00
		// 未実装
		
		// 0x4010-0x4013 = 0x00
		// 未実装
	}
	// 命令フェッチ
	lamnes::type8 CPU6502::Fetch(const address& addr)
	{
		return m_main_buss_ptr->Read(addr);
	}
	// 命令デコード
	lamnes::Addressing CPU6502::Decode(const type8& op)
	{
#if _DEBUG
		std::cerr << "\tDECODE: " << std::hex << static_cast<int>(op & 0xff) << std::endl;
#endif

		Addressing mode = Addressing::NONE;

		switch (op)
		{
		case OP::IMPLIED::SEI:
			mode = Addressing::IMPLIED;
			break;
		default:
			break;
		}

		return mode;
	}
	// 実行
	void CPU6502::Execute(const Addressing& mode, const type8 &op)
	{
		switch (mode)
		{
		case Addressing::IMPLIED:
			break;
		default:
			break;
		}
	}
	// Implied命令の実行
	void CPU6502::ExecuteImplied(const type8& op)
	{
		switch (op)
		{
		case OP::IMPLIED::SEI:
			m_status_reg = Status::I;
			m_cycles += 2;
			break;
		default:
			break;
		}
	}
}
