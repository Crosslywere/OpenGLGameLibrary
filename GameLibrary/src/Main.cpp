#include <App.h>
#include <Shader.h>
#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;

class Application : public Game::App {
public:
	virtual void OnCreate() override {
		vec3 vertices[] = {
			vec3{ 0.0f, 0.5f, 0.0f}, vec3{1.0f, 0.0f, 0.0f},
			vec3{ 0.5f,-0.5f, 0.0f}, vec3{0.0f, 1.0f, 0.0f},
			vec3{-0.5f,-0.5f, 0.0f}, vec3{0.0f, 0.0f, 1.0f},
		};
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, (void*)sizeof(vec3));
		glEnableVertexAttribArray(1);

		m_Shader = Game::Shader({
			{ "res/shaders/simple.vert.glsl", Game::Shader::VERTEX_SHADER },
			{ "res/shaders/simple.frag.glsl", Game::Shader::FRAGMENT_SHADER },
		});
		m_Shader.UseProgram();
		m_Color = glm::vec3(1.0, 0.5, 0.0);
		m_Shader.SetUniform3f("color", m_Color);
		m_Accum = 0.0;
	}

	virtual void OnUpdate(double dt) override {
		m_Accum += dt;
		if (static_cast<int>(m_Accum) % 2 == 0) {
			m_Color.r -= dt;
		}
		else {
			m_Color.r += dt;
		}
		if (static_cast<int>(m_Accum + 0.5) % 2 == 0) {
			m_Color.g += dt;
		}
		else {
			m_Color.g -= dt;
		}
		if (static_cast<int>(m_Accum + 1.0) % 2 == 0) {
			m_Color.b -= dt;
		}
		else {
			m_Color.b += dt;
		}
		m_Shader.SetUniform3f("color", m_Color);
	}

	virtual void OnRender() override {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnExit() override {
		m_Shader.DeleteShader();
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
private:
	unsigned m_VAO{}, m_VBO{};
	Game::Shader m_Shader;
	glm::vec3 m_Color;
	double m_Accum;
};

int main(int argc, char** argv) {
	Application app;
	if (app.Create("Application", 800, 600))
		app.Run();
}
