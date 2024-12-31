#include <Texture.h>

#include <Logging.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Game {

	Texture::Texture(const char* file, bool flip) {
		stbi_set_flip_vertically_on_load(flip);
		uint8_t* buffer = stbi_load(file, reinterpret_cast<int*>(&m_Width), reinterpret_cast<int*>(&m_Height), nullptr, 3);
		if (buffer) {
			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(buffer);
		}
		else {
			DEBUG_MSG("%s\n", stbi_failure_reason());
		}
	}

	void Texture::Bind(uint32_t index) const {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}

	void Texture::DeleteTexture() {
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
	}

}