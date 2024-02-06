#include "Tools/InputManager.h"

//constructeur
InputManager::InputManager() {
	timer = 0.5f;
	isRunning = nullptr;
}

//destructeur
InputManager::~InputManager() {
	delete isRunning;
}