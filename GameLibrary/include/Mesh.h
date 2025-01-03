#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#include <Layout.h>

namespace Game {

	class Mesh {
	public:
		Mesh() = default;
		Mesh(const std::vector<glm::vec3>& meshData, const Layout& layout);
		Mesh(const std::vector<glm::vec3>& meshData, const std::vector<uint32_t>& indices, const Layout& layout);
		void Draw() const;
		void DeleteMesh();
	private:
		uint32_t m_VAO{};
		uint32_t m_VBO{};
		uint32_t m_EBO{};
		uint32_t m_DrawCount{};
	};

}