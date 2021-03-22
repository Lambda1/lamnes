#ifndef __DEF_OPCODE_HPP__
#define __DEF_OPCODE_HPP__

#include "./DefType.hpp"

namespace lamnes
{
	namespace OP
	{
		namespace IMPLIED
		{
			inline static constexpr type8 SEI = static_cast<type8>(0x78);
			inline static constexpr type8 TXS = static_cast<type8>(0x9a);
		}
		namespace ACCUMULATOR
		{
		}
		namespace IMMEDIATE
		{
			inline static constexpr type8 LDX = static_cast<type8>(0xa2);
			inline static constexpr type8 LDA = static_cast<type8>(0xa9);
		}
		namespace ZEROPAGE
		{
		}
		namespace ZEROPAGE_X
		{
		}
		namespace ZEROPAGE_Y
		{
		}
		namespace RELATIVE
		{
		}
		namespace ABSOLUTE
		{
		}
		namespace ABSOLUTE_X
		{
		}
		namespace ABSOLUTE_Y
		{
		}
		namespace INDIRECT
		{
		}
		namespace INDIRECT_X
		{
		}
		namespace INDIRECT_Y
		{
		}
	}
}

#endif
