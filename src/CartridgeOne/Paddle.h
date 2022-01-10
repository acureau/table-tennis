#pragma once
#include "Game.h"

class Paddle : public Game {
public:
	// Constructors
	Paddle(const Game& gameWindow);

	// Methods
	void renderPaddle();
	void resize(char side);
	void initialize(char side);
	void physicsUpdate(char side);
	void processInput(char side);

	// Positional variables.
	int _width, _height;
	int _xPos, _yPos;
	int _r, _g, _b, _a;

private:
	// Movement variables.
	float speed = 10;
	float verticalMomentum = 0;
	float horizontalMomentum = 0;

	// Global variables.
	int callCount = 0;

	// Paddle Settings Variables
	int debounceRate = 1;
	int initialMomentum = 10;
	int maxSpeed = 25;
	float friction = 0.25;

};

