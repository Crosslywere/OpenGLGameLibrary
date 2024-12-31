#pragma once

#include <cstdint>

namespace Game {

	class Texture {
	public:
		Texture() = default;
		Texture(const char* file, bool flip = false);
		void Bind(uint32_t index) const;
		void DeleteTexture();
	private:
		uint32_t m_Texture{};
		uint32_t m_Width{};
		uint32_t m_Height{};
	};

}