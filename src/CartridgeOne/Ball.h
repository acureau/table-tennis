#pragma once
#include "Game.h"
#include "Paddle.h"

class Ball : public Game
{
public:
	// Constructors
	Ball(const Game& gameWindow);

	// Methods
	void renderBall();
	void resize();
	void initialize();
	void move();
	void processInput(Paddle* leftPaddle, Paddle* rightPaddle);
	void checkCollision(Paddle* leftPaddle, Paddle* rightPaddle);
	
	// Movement variables.
	int horizontalSpeed = 15;
	int verticalSpeed = 8;
	int verticalVelocity;
	char direction;

private:
	int _width, _height;
	int _xPos, _yPos;
	int _r, _g, _b, _a;

};