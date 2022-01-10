#include "Paddle.h"

// Constructor & Destructor
Paddle::Paddle(const Game &game): Game(game) { }

void Paddle::initialize(char side) {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Set color.
	_r = 225;
	_g = 225;
	_b = 225;
	_a = 225;

	// Calculate paddle size and position.
	_height = (windowHeight / 12);
	_width = _height;
	_yPos = ((windowHeight / 2) - (_height / 2));

	if (side == 'L') {
		_xPos = (_width / 2);
	}
	else {
		_xPos = (windowWidth - (3*(_width / 2)));
	}
}

void Paddle::resize(char side) {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Calculate paddle size and position.
	_height = (windowHeight / 12);
	_width = _height;
	_yPos = ((windowHeight / 2) - (_height / 2));

	if (side == 'L') {
		_xPos = (_width / 2);
	}
	else {
		_xPos = (windowWidth - (3 * (_width / 2)));
	}
}

void Paddle::renderPaddle() {
	// Create a rectangle on the screen with the provided information.
	SDL_Rect paddle;
	paddle.w = _width;
	paddle.h = _height;
	paddle.x = _xPos;
	paddle.y = _yPos;

	// Set color and fill the rectangle.
	SDL_SetRenderDrawColor(gameRenderer, _r, _g, _b, _a);
	SDL_RenderFillRect(gameRenderer, &paddle);
}

void Paddle::processInput(char side) {
	// Grab a list of all key states.
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	bool moved = false;

	// Control movement & increment / decrement momentum based upon movement direction.
	if (side == 'L') {
		if (keystate[SDL_SCANCODE_W]) {
			moved = true;
			_yPos -= speed;
			if (verticalMomentum >= 0) { verticalMomentum = -initialMomentum; }
			verticalMomentum--;
		}
		if (keystate[SDL_SCANCODE_A]) {
			moved = true;
			_xPos -= speed;
			if (horizontalMomentum >= 0) { horizontalMomentum = -initialMomentum; }
			horizontalMomentum--;
		}
		if (keystate[SDL_SCANCODE_S]) {
			moved = true;
			_yPos += speed;
			if (verticalMomentum <= 0) { verticalMomentum = initialMomentum; }
			verticalMomentum++;
		}
		if (keystate[SDL_SCANCODE_D]) {
			moved = true;
			_xPos += speed;
			if (horizontalMomentum <= 0) { horizontalMomentum = initialMomentum; }
			horizontalMomentum++;
		}
	}
	else {
		if (keystate[SDL_SCANCODE_UP]) {
			moved = true;
			_yPos -= speed;
			if (verticalMomentum >= 0) { verticalMomentum = -initialMomentum; }
			verticalMomentum--;
		}
		if (keystate[SDL_SCANCODE_LEFT]) {
			moved = true;
			_xPos -= speed;
			if (horizontalMomentum >= 0) { horizontalMomentum = -initialMomentum; }
			horizontalMomentum--;
		}
		if (keystate[SDL_SCANCODE_DOWN]) {
			moved = true;
			_yPos += speed;
			if (verticalMomentum <= 0) { verticalMomentum = initialMomentum; }
			verticalMomentum++;
		}
		if (keystate[SDL_SCANCODE_RIGHT]) {
			moved = true;
			_xPos += speed;
			if (horizontalMomentum <= 0) { horizontalMomentum = initialMomentum; }
			horizontalMomentum++;
		}
	}

	// Increment speed when moving.
	if (moved && speed < maxSpeed) {
		speed += 0.15;
	}
}

void Paddle::physicsUpdate(char side) {
	// Grab a list of all key states.
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	bool moving = false;
	
	// Record calls for debounce.
	callCount++;

	// Check if still moving. Remove opposite momentum if only moving in one direction.
	if (side == 'L') {
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_D]) {
			moving = true;

			// Every 'debounceRate' calls, check if moving diagonally. If not reset the opposite momentum to the current direction.
			if (callCount > debounceRate) {
				if (keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_D]) { horizontalMomentum = 0; }
				if (keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_D]) { horizontalMomentum = 0; }
				if (keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_D]) { verticalMomentum = 0; }
				if (keystate[SDL_SCANCODE_D] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S]) { verticalMomentum = 0; }
				callCount = 0;
			}
		}
	}
	else {
		if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_RIGHT]) {
			moving = true;

			// Every 'debounceRate' calls, check if moving diagonally. If not reset the opposite momentum to the current direction.
			if (callCount > debounceRate) {
				if (keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_DOWN] && !keystate[SDL_SCANCODE_RIGHT]) { horizontalMomentum = 0; }
				if (keystate[SDL_SCANCODE_DOWN] && !keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_RIGHT]) { horizontalMomentum = 0; }
				if (keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN] && !keystate[SDL_SCANCODE_RIGHT]) { verticalMomentum = 0; }
				if (keystate[SDL_SCANCODE_RIGHT] && !keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN]) { verticalMomentum = 0; }
				callCount = 0;
			}
		}
	}

	// Apply (poorly educated) physics.
	if (!moving) {
		// Reset the speed on stand-still.
		speed = 10;

		// Move the momentum to zero, and move the paddle by the conversion rate each time.
		if (!horizontalMomentum == 0) {
			_xPos += (friction * horizontalMomentum);
			if (horizontalMomentum > 0) {
				horizontalMomentum--;
			}
			else {
				horizontalMomentum++;
			}
		}
		if (!verticalMomentum == 0) {
			_yPos += (friction * verticalMomentum);
			if (verticalMomentum > 0) {
				verticalMomentum--;
			}
			else {
				verticalMomentum++;
			}
		}
	}
}