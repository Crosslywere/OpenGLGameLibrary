#include <Shader.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>

#include <Logging.h>

namespace Game {

	Shader::Shader(std::set<std::pair<const char*, Type>> shaders) {
		m_Program = glCreateProgram();
		for (const auto& shaderData : shaders) {
			uint32_t shader = CompileShaderFile(shaderData);
			glAttachShader(m_Program, shader);
			glDeleteShader(shader);
		}
		glLinkProgram(m_Program);
		int success;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512]{};
			glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
			DEBUG_MSG("%s\n", infoLog);
		}
	}

	void Shader::UseProgram() const {
		glUseProgram(m_Program);
	}

	void Shader::SetUniform1f(const char* name, float value) {
		int location = glGetUniformLocation(m_Program, name);
		glUniform1f(location, value);
	}

	void Shader::SetUniform2f(const char* name, const glm::vec2& vector) {
		int location = glGetUniformLocation(m_Program, name);
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::SetUniform3f(const char* name, const glm::vec3& vector) {
		int location = glGetUniformLocation(m_Program, name);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const char* name, const glm::vec4& vector) {
		int location = glGetUniformLocation(m_Program, name);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::DeleteShader() {
		glDeleteProgram(m_Program);
		m_Program = 0;
	}

	uint32_t Shader::CompileShaderFile(FileAndType fileAndType) {
		uint32_t shader{};
		switch (fileAndType.second) {
		case Type::VERTEX_SHADER:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Type::FRAGMENT_SHADER:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			DEBUG_MSG("'%s' was not loaded", fileAndType.first);
			return 0;
		}
		std::ifstream fs;
		fs.open(fileAndType.first);
		if (fs.is_open()) {
			std::stringstream ss;
			ss << fs.rdbuf();
			std::string source = ss.str();
			const char* sourceStr = source.c_str();
			glShaderSource(shader, 1, &sourceStr, 0);
			glCompileShader(shader);
		}
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[1000]{};
			glGetShaderInfoLog(shader, 1000, nullptr, infoLog);
			DEBUG_MSG("%s error:\n%s", fileAndType.first, infoLog);
		}
		return shader;
	}
}