#ifndef __VIRTUAL_SCREEN_HPP__
#define __VIRTUAL_SCREEN_HPP__

#include <iostream>
#include <vector>

namespace lamnes
{
	class VirtualScreen
	{
	private:
		struct col
		{
			using type = unsigned char;
			type r, g, b;
			col():	r(0), g(0), b(0) {}
			~col(){}
		};

		inline static constexpr size_t SCREEN_WIDTH = 256;
		inline static constexpr size_t SCREEN_HEIGHT = 240;

	public:
		VirtualScreen();
		~VirtualScreen();

		void Init();

	private:
		std::vector<col> m_screen_buffer;
	};
}

#endif
