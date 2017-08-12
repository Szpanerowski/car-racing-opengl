#include "InputHandler.h"

#include <gl/freeglut.h>

using namespace std;

InputHandler* InputHandler::instance = nullptr;

InputHandler* InputHandler::getInstance() {

	ensureInitialized();
	return instance;
}

void InputHandler::ensureInitialized() {

	if (instance == nullptr)
		instance = new InputHandler();
}

InputHandler::InputHandler() {

	glutSpecialFunc(handleSpecialKeyPressed);
	glutSpecialUpFunc(handleSpecialKeyReleased);

	glutKeyboardFunc(handleCharacterPressed);
	glutKeyboardUpFunc(handleCharacterReleased);
}

bool InputHandler::checkSpecialKey(int key) {

	return checkKey(key + SPECIAL_KEY_OFFSET);
}

bool InputHandler::checkCharacter(unsigned char character) {

	return checkKey(character);
}

bool InputHandler::checkKey(int key) {

	map<int, bool>::const_iterator findResult = keyPressed.find(key);

	if (findResult != keyPressed.end())
		return findResult->second;

	return false;
}

void InputHandler::handleCharacterPressed(unsigned char character, int mouseX, int mouseY) {

	InputHandler::getInstance()->handleKeyPressed(character);
}

void InputHandler::handleCharacterReleased(unsigned char character, int mouseX, int mouseY) {

	InputHandler::getInstance()->handleKeyReleased(character);
}

void InputHandler::handleSpecialKeyPressed(int key, int mouseX, int mouseY) {

	InputHandler::getInstance()->handleKeyPressed(key + SPECIAL_KEY_OFFSET);
}

void InputHandler::handleSpecialKeyReleased(int key, int mouseX, int mouseY) {

	InputHandler::getInstance()->handleKeyReleased(key + SPECIAL_KEY_OFFSET);
}

void InputHandler::handleKeyPressed(int key) {

	keyPressed[key] = true;
}

void InputHandler::handleKeyReleased(int key) {

	keyPressed.erase(key);
}