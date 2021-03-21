#ifndef __DEF_ADDRESSING_HPP__
#define __DEF_ADDRESSING_HPP__

#include "./DefType.hpp"

namespace lamnes
{
	enum class Addressing : type16
	{
		NONE = static_cast<type16>(0x00),
		IMPLIED = static_cast<type16>(0x01),
	};
}

#endif