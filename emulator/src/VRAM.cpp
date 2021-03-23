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

	// ‰Šú‰»ˆ—
	void VRAM::Init()
	{
	}
	// ƒf[ƒ^‘‚«‚İ
	void VRAM::Write(const address& addr, const type8& val)
	{
		m_vram[addr] = val;
	}
}
