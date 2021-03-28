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
			inline static constexpr type8 DEY = static_cast<type8>(0x88);
			inline static constexpr type8 TXS = static_cast<type8>(0x9a);
			inline static constexpr type8 CLD = static_cast<type8>(0xd8);
			inline static constexpr type8 INX = static_cast<type8>(0xe8);
		}
		namespace ACCUMULATOR
		{
		}
		namespace IMMEDIATE
		{
			inline static constexpr type8 LDY = static_cast<type8>(0xa0);
			inline static constexpr type8 LDX = static_cast<type8>(0xa2);
			inline static constexpr type8 LDA = static_cast<type8>(0xa9);
			inline static constexpr type8 CMP = static_cast<type8>(0xc9);
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
			inline static constexpr type8 BPL = static_cast<type8>(0x10);
			inline static constexpr type8 BNE = static_cast<type8>(0xd0);
		}
		namespace ABSOLUTE
		{
			inline static constexpr type8 JMP = static_cast<type8>(0x4c);
			inline static constexpr type8 STA = static_cast<type8>(0x8d);
			inline static constexpr type8 LDA = static_cast<type8>(0xad);
		}
		namespace ABSOLUTE_X
		{
			inline static constexpr type8 LDA = static_cast<type8>(0xbd);
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
