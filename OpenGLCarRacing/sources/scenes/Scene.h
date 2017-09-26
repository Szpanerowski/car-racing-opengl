#pragma once

class Scene {

private:

	static int currentTime;
	static Scene* currentScene;

	static void renderFrame();
	static void timerTick(int value);

protected:

	virtual void update(float deltaSeconds) = 0;
	virtual void render() = 0;

public:

	void load();
};