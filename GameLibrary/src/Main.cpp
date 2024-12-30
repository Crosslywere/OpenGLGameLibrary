#include <App.h>
#include <Shader.h>
#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using glm::vec2;
using glm::vec3;

class Application : public Game::App {
public:
	virtual void OnCreate() override {
		vec3 vertices[] = {
			vec3{ 0.5f, 0.5f, 0.0f}, vec3{1.0f, 1.0f, 0.0f}, vec3{1.0f, 0.0f, 0.0f},
			vec3{ 0.5f,-0.5f, 0.0f}, vec3{1.0f, 0.0f, 0.0f}, vec3{0.0f, 1.0f, 0.0f},
			vec3{-0.5f,-0.5f, 0.0f}, vec3{0.0f, 0.0f, 0.0f}, vec3{0.0f, 0.0f, 1.0f},
			vec3{-0.5f, 0.5f, 0.0f}, vec3{0.0f, 1.0f, 0.0f}, vec3{1.0f, 1.0f, 1.0f},
		};
		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0,
		};
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 3, reinterpret_cast<void*>(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 3, reinterpret_cast<void*>(sizeof(vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 3, reinterpret_cast<void*>(sizeof(vec3) * 2));
		glEnableVertexAttribArray(2);

		m_Shader = Game::Shader({
			{ "res/shaders/simple.vert.glsl", Game::Shader::VERTEX_SHADER },
			{ "res/shaders/simple.frag.glsl", Game::Shader::FRAGMENT_SHADER },
		});
		m_Shader.UseProgram();
		m_Color = glm::vec3(1.0, 0.5, 0.0);
		m_Shader.SetUniform3f("color", m_Color);
		m_Accum = 0.0;

		int width{}, height{};
		uint8_t* data = stbi_load("res/images/brick.jpg", &width, &height, nullptr, 3);
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	virtual void OnExit() override {
		glDeleteTextures(1, &m_Texture);
		m_Shader.DeleteShader();
		glDeleteBuffers(1, &m_EBO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
private:
	unsigned m_VAO{}, m_VBO{}, m_EBO{}, m_Texture;
	Game::Shader m_Shader;
	glm::vec3 m_Color;
	double m_Accum;
};

int main(int argc, char** argv) {
	Application app;
	if (app.Create("Application", 800, 600))
		app.Run();
}
