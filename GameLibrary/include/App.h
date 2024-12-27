#pragma once

#include <string>

namespace Game {
	class App {
	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(double dt) {};
		virtual void OnRender() {};
		virtual void OnExit() {}
	public:
		static enum GLVersionFlags {
			GL_3_3,
			GL_4_0,
			GL_4_1,
			GL_4_2,
			GL_4_3,
			GL_4_4,
			GL_4_5,
			GL_4_6,
			GL_MIN = GL_3_3,
			GL_MAX = GL_4_6,
		};
		bool Create(const std::string& title, uint32_t width = 800, uint32_t height = 450, GLVersionFlags versionFlag = GL_MIN);
		void Run();
	};
}