#pragma once

class Scene {

private:

	static Scene* currentScene;
	static void renderFrame();
	static void timerTick(int value);

protected:

	virtual void update() = 0;
	virtual void render() = 0;

public:

	void load();
};