#include <App.h>
#include <Shader.h>
#include <Texture.h>
#include <Layout.h>
#include <Mesh.h>
#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;

class Application : public Game::App {
public:
	virtual void OnCreate() override {
		std::vector<vec3> vertices = {
			vec3{ 0.5f, 0.5f, 0.0f}, vec3{1.0f, 1.0f, 0.0f}, vec3{1.0f, 0.0f, 0.0f},
			vec3{ 0.5f,-0.5f, 0.0f}, vec3{1.0f, 0.0f, 0.0f}, vec3{0.0f, 1.0f, 0.0f},
			vec3{-0.5f,-0.5f, 0.0f}, vec3{0.0f, 0.0f, 0.0f}, vec3{0.0f, 0.0f, 1.0f},
			vec3{-0.5f, 0.5f, 0.0f}, vec3{0.0f, 1.0f, 0.0f}, vec3{1.0f, 1.0f, 1.0f},
		};
		std::vector<uint32_t> indices = {
			0, 1, 2,
			2, 3, 0,
		};
		m_Mesh = Game::Mesh(vertices, indices, Game::Layout().Append(ENABLED_VEC3).Append(ENABLED_VEC3).Append(ENABLED_VEC3));

		m_Shader = Game::Shader({
			{ "res/shaders/simple.vert.glsl", Game::Shader::VERTEX_SHADER },
			{ "res/shaders/simple.frag.glsl", Game::Shader::FRAGMENT_SHADER },
		});
		m_Shader.UseProgram();
		m_Color = glm::vec3(1.0f, 0.5f, 0.0f);
		m_Shader.SetUniform3f("color", m_Color);

		m_Texture = Game::Texture("res/images/brick.jpg");
		m_Shader.SetTextureUniform("brickTexture", m_Texture);
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
		m_Mesh.Draw();
	}

	virtual void OnExit() override {
		m_Texture.DeleteTexture();
		m_Shader.DeleteShader();
		m_Mesh.DeleteMesh();
	}
private:
	Game::Shader m_Shader;
	Game::Texture m_Texture;
	Game::Mesh m_Mesh;
	glm::vec3 m_Color{};
	double m_Accum{};
};

int main(int argc, char** argv) {
	Application app;
	if (app.Create("Application", 800, 600)) {
		app.Run();
		exit(EXIT_SUCCESS);
	}
	else {
		exit(EXIT_FAILURE);
	}
}
