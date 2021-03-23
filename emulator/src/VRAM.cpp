#include "VRAM.hpp"

namespace lamnes
{
	VRAM::VRAM()
	{
		m_vram.resize(VRAM_SIZE, 0);
	}

	VRAM::~VRAM()
	{
	}

	// 初期化処理
	void VRAM::Init()
	{
	}
	// データ書き込み
	void VRAM::Write(const address& addr, const type8& data)
	{
		m_vram[addr] = data;
	}
}
