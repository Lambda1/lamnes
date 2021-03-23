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
	void VRAM::Write(const address& addr, const type8& data)
	{
		m_vram[addr] = data;
	}
}
