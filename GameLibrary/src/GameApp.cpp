#include <GameApp.h>
#include <chrono>

inline struct ApplicationState {
	bool running = false;
	bool vsync = false;
	bool fullscreen = false;
} appState;

static void CleanUp() {
}

bool GameApp::Create(const std::string& title, uint32_t width, uint32_t height) {

	appState.running = true;
	return true;
}

void GameApp::Run() {
	auto past = std::chrono::high_resolution_clock::now();
	OnCreate();
	while (appState.running) {
		auto now = std::chrono::high_resolution_clock::now();
		double dt = (now - past).count() / 1000000000.0;
		past = now;
		OnUpdate(dt);
		OnRender();
	}
	CleanUp();
}
