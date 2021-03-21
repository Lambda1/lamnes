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
		PowerUp();
		Reset();
	}

	// リセット処理
	void CPU6502::Reset()
	{
		m_status_reg = Status::I; // 割り込み禁止
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
	CPU6502::type16 CPU6502::Fetch(const type16& address)
	{
		return type16();
	}
}
