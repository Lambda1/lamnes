#include "VirtualScreen.hpp"

namespace lamnes
{
	VirtualScreen::VirtualScreen()
	{
		m_screen_buffer.resize(SCREEN_WIDTH * SCREEN_HEIGHT, {});
	}
	VirtualScreen::~VirtualScreen()
	{
	}

	// ������
	void VirtualScreen::Init()
	{
	}
}
