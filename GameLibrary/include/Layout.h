#pragma once

#include <cstdint>
#include <vector>

namespace Game {

	struct AttribData {
		int size = 1;
		bool enabled = false;
	};

	class Layout {
	public:
		Layout() = default;
		Layout& Append(const AttribData& attribData);
		void Apply() const;
		inline const uint32_t GetWidth() const {
			return m_Stride / m_Attribs.size();
		}
	private:
		uint32_t m_Stride{};
		std::vector<AttribData> m_Attribs;
	};

}

#define ENABLED_VEC1 { 1, true }
#define DISABLE_VEC1 { 1,false }
#define ENABLED_VEC2 { 2, true }
#define DISABLE_VEC2 { 2,false }
#define ENABLED_VEC3 { 3, true }
#define DISABLE_VEC3 { 3,false }
#define ENABLED_VEC4 { 4, true }
#define DISABLE_VEC4 { 4,false }
