#include "Net.h"

Net::Net(const Game& game) : Game(game) { }

void Net::initialize() {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Set color.
	_r = 225;
	_g = 225;
	_b = 225;
	_a = 225;

	// Calculate net size and position.
	_height = windowHeight;
	_width = 0.8 * (windowWidth / 28);
	_yPos = 0;
	_xPos = ((windowWidth / 2) - (_width / 2));
}

void Net::resize() {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Calculate new size and position.
	_height = windowHeight;
	_width = 0.8 * (windowWidth / 28);
	_yPos = 0;
	_xPos = ((windowWidth / 2) - (_width / 2));
}

void Net::processInput() {
	// Grab a list of all key states.
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_9]) {
		_xPos -= 8;
	}
	if (keystate[SDL_SCANCODE_0]) {
		_xPos += 8;
	}
}

void Net::renderNet() {
	SDL_Rect net;

	net.w = _width;
	net.h = _height;
	net.x = _xPos;
	net.y = _yPos;

	SDL_SetRenderDrawColor(gameRenderer, _r, _g, _b, _a);
	SDL_RenderFillRect(gameRenderer, &net);
}