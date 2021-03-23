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

	// ����������
	void VRAM::Init()
	{
	}
	// �f�[�^��������
	void VRAM::Write(const address& addr, const type8& val)
	{
		m_vram[addr] = val;
	}
}
