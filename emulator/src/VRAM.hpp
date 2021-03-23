#ifndef __VRAM_HPP__
#define __VRAM_HPP__

#include <iostream>
#include <vector>

#include "./DefType.hpp"

namespace lamnes
{
class VRAM
{
private:
	inline static constexpr size_t VRAM_SIZE = 2048;
public:
	VRAM();
	~VRAM();

	void Init();

	void Write(const address &addr, const type8 &data);

private:
	std::vector<type8> m_vram;
};
}

#endif
