#include <GameApp.h>
#include <cstdio>

class Application : public GameApp {
public:
	virtual void OnCreate() override {
	}

	virtual void OnUpdate(double dt) override {
	}

	virtual void OnRender() override {
	}
};

int main(int argc, char** argv) {
	Application app;
	if (app.Create("Application", 800, 450))
		app.Run();
}
