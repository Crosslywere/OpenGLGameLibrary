#include <Mesh.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <Logging.h>

namespace Game {

	Mesh::Mesh(const std::vector<glm::vec3>& meshData, const Layout& layout) {
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(glm::vec3), meshData.data(), GL_STATIC_DRAW);

		layout.Apply();

		m_DrawCount = meshData.size() / layout.GetWidth();
	}

	Mesh::Mesh(const std::vector<glm::vec3>& meshData, const std::vector<uint32_t>& indices, const Layout& layout) {
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(glm::vec3), meshData.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

		layout.Apply();

		m_DrawCount = indices.size();
	}

	void Mesh::Draw() const {
		glBindVertexArray(m_VAO);
		if (m_EBO) {
			glDrawElements(GL_TRIANGLES, m_DrawCount, GL_UNSIGNED_INT, nullptr);
			return;
		}
		glDrawArrays(GL_TRIANGLES, 0, m_DrawCount);
	}

	void Mesh::DeleteMesh() {
		glDeleteBuffers(1, &m_EBO);
		m_EBO = 0;
		glDeleteBuffers(1, &m_VBO);
		m_VBO = 0;
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}

}