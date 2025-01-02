#pragma once

#include <set>
#include <glm/glm.hpp>

#include <Texture.h>

namespace Game {

	class Shader {
	public:
		enum Type {
			NONE_SHADER = 0,
			VERTEX_SHADER,
			FRAGMENT_SHADER,
		};
		using FileAndType = std::pair<const char*, Type>;
		Shader() = default;
		Shader(std::set<FileAndType> shaders);
		void UseProgram() const;
		void SetUniform1f(const char* name, float value) const;
		void SetUniform2f(const char* name, const glm::vec2& vector) const;
		void SetUniform3f(const char* name, const glm::vec3& vector) const;
		void SetUniform4f(const char* name, const glm::vec4& vector) const;
		void SetUniform1i(const char* name, int value) const;
		void SetUniform2i(const char* name, const glm::ivec2& vector) const;
		void SetUniform3i(const char* name, const glm::ivec3& vector) const;
		void SetUniform4i(const char* name, const glm::ivec4& vector) const;
		void SetUniformMat3(const char* name, const glm::mat3& mat) const;
		void SetUniformMat4(const char* name, const glm::mat4& mat) const;
		void SetTextureUniform(const char* name, const Texture& texture, int index = 0) const;
		void DeleteShader();
	private:
		uint32_t m_Program{};
		static uint32_t CompileShaderFile(FileAndType fileAndType);
	};

}