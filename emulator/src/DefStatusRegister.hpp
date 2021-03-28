#ifndef __DEF_STATUS_REGISTER_HPP__
#define __DEF_STATUS_REGISTER_HPP__

#include "./DefType.hpp"

namespace lamnes
{
	namespace Status
	{
		inline static constexpr type8 N = static_cast<type8>(0x80);
		inline static constexpr type8 V = static_cast<type8>(0x40);
		inline static constexpr type8 R = static_cast<type8>(0x20);
		inline static constexpr type8 B = static_cast<type8>(0x10);
		inline static constexpr type8 D = static_cast<type8>(0x08);
		inline static constexpr type8 I = static_cast<type8>(0x04);
		inline static constexpr type8 Z = static_cast<type8>(0x02);
		inline static constexpr type8 C = static_cast<type8>(0x01);
	}
}

#endif
