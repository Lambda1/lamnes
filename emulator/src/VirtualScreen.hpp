#ifndef __VIRTUAL_SCREEN_HPP__
#define __VIRTUAL_SCREEN_HPP__

#include <iostream>
#include <iomanip>
#include <vector>

namespace lamnes
{
	class VirtualScreen
	{
	private:
		using type = unsigned char;
		
		struct col
		{
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

		void Render(const size_t &x, const size_t &y, const type &r, const type &g, const type &b);

		void Output();

	private:
		std::vector<col> m_screen_buffer;
	};
}

#endif
