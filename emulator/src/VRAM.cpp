#include "VRAM.hpp"

namespace lamnes
{
	VRAM::VRAM()
	{
		m_vram.resize(VRAM_SIZE, 0);
	}

	VRAM::~VRAM()
	{
	}

	// 初期化処理
	void VRAM::Init()
	{
	}
	// データ書き込み
	void VRAM::Write(const address& addr, const type8& data)
	{
		m_vram[addr] = data;
	}

	// ネームテーブルをテキスト表示
	void VRAM::DebugRenderNameTable(const int &num)
	{
		// 画面サイズ: 256*240
		// タイル: 32*30
		constexpr size_t width = 32;
		constexpr size_t height = 30;
		
		std::cerr << "NameTable: " << num << std::endl;
		for (size_t i = 0;i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				std::cerr << std::setw(2) << ((int)m_vram[i * height + j]) << " ";
			}
			std::cerr << std::endl;
		}
	}
	// 属性テーブルをテキスト表示
	void VRAM::DebugRenderAttributeTable(const int& num)
	{
		// 32 * 30
		constexpr size_t width = 32;
		constexpr size_t height = 2;
		constexpr size_t height_bias = 30;

		std::cerr << "AttributeTable: " << num << std::endl;
		for (size_t i = height_bias;i < (height_bias+height); ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				std::cerr << std::setw(2) << ((int)m_vram[i * height + j]) << " ";
			}
			std::cerr << std::endl;
		}
	}
}
