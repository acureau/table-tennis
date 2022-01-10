#include "Ball.h"

Ball::Ball(const Game& game) : Game(game) { }

void Ball::initialize() {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Set color.
	_r = 225;
	_g = 225;
	_b = 225;
	_a = 225;

	// Calculate ball size and position.
	_height = windowHeight / 24;
	_width = _height;
	_yPos = (0 - _height);
	_xPos = (0 - _width);
}

void Ball::resize() {
	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Calculate ball size and position. Reset direction.
	direction = NULL;
	_height = windowHeight / 24;
	_width = _height;
	_yPos = (0 - _height);
	_xPos = (0 - _width);
}

void Ball::renderBall() {
	SDL_Rect ball;

	ball.w = _width;
	ball.h = _height;
	ball.x = _xPos;
	ball.y = _yPos;

	SDL_SetRenderDrawColor(gameRenderer, _r, _g, _b, _a);
	SDL_RenderFillRect(gameRenderer, &ball);
}

void Ball::move() {
	if (direction == 'L') {
		_xPos -= horizontalSpeed;
	}
	else if (direction == 'R') {
		_xPos += horizontalSpeed;
	}
}

void Ball::processInput(Paddle* leftPaddle, Paddle* rightPaddle) {
	// Grab a list of all key states.
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (direction == 'L') {
		// Right paddle controls the ball's vertical movement.
		if (keystate[SDL_SCANCODE_APOSTROPHE]) {
			_yPos -= verticalSpeed;
		}
		if (keystate[SDL_SCANCODE_SLASH]) {
			_yPos += verticalSpeed;
		}
	}
	else if (direction == 'R') {
		// Left paddle controls the ball's vertical movement.
		if (keystate[SDL_SCANCODE_R]) {
			_yPos -= verticalSpeed;
		}
		if (keystate[SDL_SCANCODE_F]) {
			_yPos += verticalSpeed;
		}
	}

	// Grab window size for calculations.
	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

	// Both reset buttons can control the reset regardless of direction.
	if (keystate[SDL_SCANCODE_E]) {
		_yPos = (windowHeight / 2) - (_height / 2);
		_xPos = (0 - (2*(_width)));
		direction = 'R';
	}
	if (keystate[SDL_SCANCODE_SEMICOLON]) {
		_yPos = (windowHeight / 2) - (_height / 2);
		_xPos = windowWidth + _width;
		direction = 'L';
	}

	// Increase and decrease ball speed.
	if (keystate[SDL_SCANCODE_MINUS]) {
		if (horizontalSpeed > 5) {
			horizontalSpeed--;
		}
	}
	if (keystate[SDL_SCANCODE_EQUALS]) {
		if (horizontalSpeed < 30) {
			horizontalSpeed++;
		}
	}
	verticalSpeed = (horizontalSpeed / 1.875);
}

void Ball::checkCollision(Paddle* leftPaddle, Paddle* rightPaddle) {
	// If colliding with a paddle, reverse direction.
	if ((leftPaddle->_xPos < _xPos + _width) && (leftPaddle->_xPos + leftPaddle->_width > _xPos) && (leftPaddle->_yPos < _yPos + _height) && (leftPaddle->_yPos + leftPaddle->_height > _yPos)) {
		if (direction == 'L') {
			direction = 'R';
		}
	}
	if ((rightPaddle->_xPos < _xPos + _width) && (rightPaddle->_xPos + rightPaddle->_width > _xPos) && (rightPaddle->_yPos < _yPos + _height) && (rightPaddle->_yPos + rightPaddle->_height > _yPos)) {
		if (direction == 'R') {
			direction = 'L';
		}
	}
}