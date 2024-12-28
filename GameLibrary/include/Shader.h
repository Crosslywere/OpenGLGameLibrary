#pragma once

#include <set>
#include <glm/glm.hpp>

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
		void SetUniform1f(const char* name, float value);
		void SetUniform2f(const char* name, const glm::vec2& vector);
		void SetUniform3f(const char* name, const glm::vec3& vector);
		void SetUniform4f(const char* name, const glm::vec4& vector);
		void DeleteShader();
	private:
		uint32_t m_Program{};
		static uint32_t CompileShaderFile(FileAndType fileAndType);
	};

}