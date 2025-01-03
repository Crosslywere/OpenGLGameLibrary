#include <Layout.h>

#include <glad/glad.h>

#include <Logging.h>

namespace Game {

	Layout& Layout::Append(const AttribData& attribData) {
		m_Attribs.push_back(attribData);
		m_Stride += attribData.size;
		return *this;
	}

	void Layout::Apply() const {
		int index = 0;
		int offset = 0;
		for (const auto& attrib : m_Attribs) {
			glVertexAttribPointer(index, attrib.size, GL_FLOAT, GL_FALSE, m_Stride * sizeof(float), reinterpret_cast<void*>(offset));
			if (attrib.enabled) {
				glEnableVertexAttribArray(index);
			}
			offset += attrib.size * sizeof(float);
			index++;
		}
	}

}