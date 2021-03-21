#ifndef __DEF_STATUS_REGISTER_HPP__
#define __DEF_STATUS_REGISTER_HPP__

namespace lamnes
{
	namespace Status
	{
		using type = char;
		
		inline static constexpr type N = static_cast<type>(0x80);
		inline static constexpr type V = static_cast<type>(0x40);
		inline static constexpr type R = static_cast<type>(0x20);
		inline static constexpr type B = static_cast<type>(0x10);
		inline static constexpr type D = static_cast<type>(0x08);
		inline static constexpr type I = static_cast<type>(0x04);
		inline static constexpr type Z = static_cast<type>(0x02);
		inline static constexpr type C = static_cast<type>(0x01);
	}
}

#endif
