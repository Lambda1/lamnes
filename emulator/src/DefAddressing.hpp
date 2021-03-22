#ifndef __DEF_ADDRESSING_HPP__
#define __DEF_ADDRESSING_HPP__

#include "./DefType.hpp"

namespace lamnes
{
	enum class Addressing : type16
	{
		NONE = static_cast<type16>(0x0000),
		IMPLIED = static_cast<type16>(0x0001),
		ACCUMULATOR = static_cast<type16>(0x0002),
		IMMEDIATE = static_cast<type16>(0x0004),
		ZEROPAGE = static_cast<type16>(0x0008),
		ZEROPAGE_X = static_cast<type16>(0x0010),
		ZEROPAGE_Y = static_cast<type16>(0x0020),
		RELATIVE = static_cast<type16>(0x0040),
		ABSOLUTE = static_cast<type16>(0x0080),
		ABSOLUTE_X = static_cast<type16>(0x0100),
		ABSOLUTE_Y = static_cast<type16>(0x0200),
		INDIRECT = static_cast<type16>(0x0400),
		INDIRECT_X = static_cast<type16>(0x0800),
		INDIRECT_Y = static_cast<type16>(0x1000),
	};
}

#endif