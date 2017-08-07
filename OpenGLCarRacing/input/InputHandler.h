#pragma once

#include <map>

class InputHandler
{

private:

	static const int SPECIAL_KEY_OFFSET = 256;

	static InputHandler* instance;

	std::map<int, bool> keyPressed;

	InputHandler();	

	static void handleSpecialKeyPressed(int key, int mouseX, int mouseY);
	static void handleSpecialKeyReleased(int key, int mouseX, int mouseY);

	static void handleCharacterPressed(unsigned char character, int mouseX, int mouseY);
	static void handleCharacterReleased(unsigned char character, int mouseX, int mouseY);

	void handleKeyPressed(int key);
	void handleKeyReleased(int key);

	bool checkKey(int key);

public:

	static void ensureInitialized();
	static InputHandler* getInstance();

	bool checkSpecialKey(int key);
	bool checkCharacter(unsigned char character);
};

