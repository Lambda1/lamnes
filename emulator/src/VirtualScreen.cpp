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

	// èâä˙âª
	void VirtualScreen::Init()
	{
	}

	// ï`âÊ
	void VirtualScreen::Render(const size_t& x, const size_t& y, const type& r, const type& g, const type& b)
	{
		m_screen_buffer[y * SCREEN_WIDTH + x].r = r;
		m_screen_buffer[y * SCREEN_WIDTH + x].g = g;
		m_screen_buffer[y * SCREEN_WIDTH + x].b = b;
	}
	// èoóÕ
	void VirtualScreen::Output()
	{
		for (size_t i = 0; i < SCREEN_HEIGHT; ++i)
		{
			for (size_t j = 0; j < SCREEN_WIDTH; ++j)
			{
				auto val = (int)(m_screen_buffer[i * SCREEN_WIDTH + j].r & 0xff);
				std::cout << std::setw(2) << val;
			}
			std::cout << std::endl;
		}
	}
}
