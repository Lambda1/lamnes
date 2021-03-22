#include "./CPU6502.hpp"

#include "./MainBuss.hpp"

namespace lamnes
{
	/* public */

	CPU6502::CPU6502() :
		m_accumulator{ 0 },
		m_idx_reg_x{ 0 }, m_idx_reg_y{ 0 },
		m_stack_ptr_value{ 0 },
		m_status_reg{ 0 },
		m_pc{ 0 },
		m_cycles{ 0 },
		m_main_buss_ptr{ nullptr }
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
		m_pc = static_cast<address>(Fetch(0xfffc) & 0xff) | static_cast<address>(((Fetch(0xfffd) & 0xff) << 8));
	}
	// 処理実行
	void CPU6502::Step()
	{
		type8 op = Fetch(m_pc++);
		Addressing mode = Decode(op);
		Execute(mode, op);
	}

	// デバッグ用メモリ内容表示
	void CPU6502::DebugPrint()
	{
		std::cout << "\n" << "CYCLE : " << m_cycles << std::endl;
		std::cout << "ACCUML: " << std::hex << static_cast<int>(m_accumulator & 0xff) << std::endl;
		std::cout << "IDX   : " << std::hex << static_cast<int>(m_idx_reg_x & 0xff) << "," << static_cast<int>(m_idx_reg_y & 0xff) << std::endl;
		std::cout << "PGCNT : " << std::hex << m_pc << std::endl;
		std::cout << "STATUS: " << std::hex << static_cast<int>(m_status_reg & 0xff) << std::endl;
	}

	/* private */

	// 電源投入処理
	void CPU6502::PowerUp()
	{
		m_pc = static_cast<type16>(0x34);
		m_accumulator = static_cast<type8>(0x00);
		m_idx_reg_x = static_cast<type8>(0x00);
		m_idx_reg_y = static_cast<type8>(0x00);
		m_stack_ptr_value = static_cast<type8>(0xfd);

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
		Addressing mode = Addressing::NONE;

		switch (op)
		{
		case OP::IMPLIED::SEI:
		case OP::IMPLIED::DEY:
		case OP::IMPLIED::TXS:
		case OP::IMPLIED::INX:
			mode = Addressing::IMPLIED; break;
		case OP::IMMEDIATE::LDY:
		case OP::IMMEDIATE::LDX:
		case OP::IMMEDIATE::LDA:
			mode = Addressing::IMMEDIATE; break;
		case OP::RELATIVE::BNE:
			mode = Addressing::RELATIVE; break;
		case OP::ABSOLUTE::STA:
			mode = Addressing::ABSOLUTE; break;
		case OP::ABSOLUTE_X::LDA:
			mode = Addressing::ABSOLUTE_X; break;
		default:
			break;
		}

#if _DEBUG
		std::cerr << "\tDECODE: " << std::hex << static_cast<int>(op & 0xff);
		std::cerr << " : " << std::hex << static_cast<int>(mode) << std::endl;
#endif

		return mode;
	}
	// 実行
	void CPU6502::Execute(const Addressing& mode, const type8& op)
	{
		switch (mode)
		{
		case Addressing::IMPLIED:
			ExecuteImplied(op);	break;
		case Addressing::ACCUMULATOR:
			ExecuteAccumulator(op);	break;
		case Addressing::IMMEDIATE:
			ExecuteImmediate(op); break;
		case Addressing::ZEROPAGE:
			ExecuteZeropage(op); break;
		case Addressing::ZEROPAGE_X:
			ExecuteZeropageX(op); break;
		case Addressing::ZEROPAGE_Y:
			ExecuteZeropageY(op); break;
		case Addressing::RELATIVE:
			ExecuteRelative(op); break;
		case Addressing::ABSOLUTE:
			ExecuteAbsolute(op); break;
		case Addressing::ABSOLUTE_X:
			ExecuteAbsoluteX(op); break;
		case Addressing::ABSOLUTE_Y:
			ExecuteAbsoluteY(op); break;
		case Addressing::INDIRECT:
			ExecuteIndirect(op); break;
		case Addressing::INDIRECT_X:
			ExecuteIndirectX(op); break;
		case Addressing::INDIRECT_Y:
			ExecuteIndirectY(op); break;
		default:
			std::cerr << "Opcode is not found." << std::endl;
			std::exit(EXIT_FAILURE);
			break;
		}
	}
	void CPU6502::ExecuteImplied(const type8& op)
	{
		switch (op)
		{
		case OP::IMPLIED::SEI:
			m_status_reg = Status::I;
			m_cycles += 2;
			break;
		case OP::IMPLIED::DEY:
			--m_idx_reg_y;
			SetZN(m_idx_reg_y);
			m_cycles += 2;
			break;
		case OP::IMPLIED::TXS:
			m_stack_ptr_value = m_idx_reg_x;
			SetZN(m_stack_ptr_value);
			m_cycles += 2;
			break;
		case OP::IMPLIED::INX:
			++m_idx_reg_x;
			SetZN(m_idx_reg_x);
			m_cycles += 2;
			break;
		default:
			break;
		}
	}
	void CPU6502::ExecuteAccumulator(const type8& op)
	{
	}
	void CPU6502::ExecuteImmediate(const type8& op)
	{
		switch (op)
		{
		case OP::IMMEDIATE::LDY:
			m_idx_reg_y = Fetch(m_pc++);
			SetZN(m_idx_reg_y);
			m_cycles += 2;
			break;
		case OP::IMMEDIATE::LDX:
			m_idx_reg_x = Fetch(m_pc++);
			SetZN(m_idx_reg_x);
			m_cycles += 2;
			break;
		case OP::IMMEDIATE::LDA:
			m_accumulator = Fetch(m_pc++);
			SetZN(m_accumulator);
			m_cycles += 2;
			break;
		default:
			break;
		}
	}
	void CPU6502::ExecuteZeropage(const type8& op)
	{
	}
	void CPU6502::ExecuteZeropageX(const type8& op)
	{
	}
	void CPU6502::ExecuteZeropageY(const type8& op)
	{
	}
	void CPU6502::ExecuteRelative(const type8& op)
	{
		switch (op)
		{
		case OP::RELATIVE::BNE:
		{
			type8 data = Fetch(m_pc++);
			if (!isStatusFlag(Status::Z))
			{
				// data: [-128,127]
				// m_pc: [0,65535]
				// 相対アドレッシングを計算するため一時的に負数を扱うように型変換する．
				m_pc = static_cast<address>(static_cast<int>(m_pc) + static_cast<int>(data));
			}
			m_cycles += 2;
		}
		break;
		default:
			break;
		}
	}
	void CPU6502::ExecuteAbsolute(const type8& op)
	{
		switch (op)
		{
		case OP::ABSOLUTE::STA:
			m_main_buss_ptr->Write(GetAddressFromPC(), m_accumulator);
			m_status_reg = 0;
			m_cycles += 4;
			break;
		default:
			break;
		}
	}
	void CPU6502::ExecuteAbsoluteX(const type8& op)
	{
		switch (op)
		{
		case OP::ABSOLUTE_X::LDA:
			m_accumulator = m_main_buss_ptr->Read(GetAddressFromPC() + static_cast<address>(m_idx_reg_x & 0xff));
			SetZN(m_accumulator);
			m_cycles += 4;
			break;
		default:
			break;
		}
	}
	void CPU6502::ExecuteAbsoluteY(const type8& op)
	{
	}
	void CPU6502::ExecuteIndirect(const type8& op)
	{
	}
	void CPU6502::ExecuteIndirectX(const type8& op)
	{
	}
	void CPU6502::ExecuteIndirectY(const type8& op)
	{
	}

	// フラグZ,Nの設定
	void CPU6502::SetZN(const type8& val)
	{
		m_status_reg = 0;
		if (val == 0)
		{
			m_status_reg |= Status::Z;
		}
		if ((val & Status::N) == Status::N)
		{
			m_status_reg |= Status::N;
		}
	}

	// フラグ確認
	bool CPU6502::isStatusFlag(const type8& flag)
	{
		if ((m_status_reg & flag) == flag) { return true; }
		return false;
	}

	// 2バイトのアドレス取得
	address CPU6502::GetAddressFromPC()
	{
		address low = static_cast<address>(Fetch(m_pc++) & 0xff);
		address high = static_cast<address>(Fetch(m_pc++) & 0xff) << 8;
		return (high | low);
	}
}
