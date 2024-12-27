#include <App.h>
#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Application : public Game::App {
public:
	virtual void OnCreate() override {
		glm::vec2 vertices[] = {
			glm::vec2{ 0.0f, 1.0f},
			glm::vec2{ 1.0f,-1.0f},
			glm::vec2{-1.0f,-1.0f},
		};
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(0);

		m_Program = glCreateProgram();

		const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos, 1.0);
}
)";
		unsigned vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertexShaderSource, 0);
		glCompileShader(vertShader);
		glAttachShader(m_Program, vertShader);

		const char* fragmentShaderSource = R"(
#version 330 core

void main() {
	gl_FragColor = vec4(1.0, 0.5, 0.125, 1.0);
}
)";
		unsigned fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragmentShaderSource, 0);
		glCompileShader(fragShader);

		glAttachShader(m_Program, fragShader);
		glLinkProgram(m_Program);
		glUseProgram(m_Program);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	virtual void OnRender() override {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnExit() override {
		glDeleteProgram(m_Program);
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
private:
	unsigned m_VAO{}, m_VBO{}, m_Program{};
};

int main(int argc, char** argv) {
	Application app;
	if (app.Create("Application", 800, 450))
		app.Run();
}
