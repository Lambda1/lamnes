#ifndef __VRAM_HPP__
#define __VRAM_HPP__

#include <iostream>
#include <iomanip>
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

	void DebugRenderNameTable(const int &num);
	void DebugRenderAttributeTable(const int& num);

private:
	std::vector<type8> m_vram;
};
}

#endif
