#pragma once
#include "Game.h"

class Net: public Game 
{
public:
	// Constructors
	Net(const Game& gameWindow);

	// Methods
	void renderNet();
	void resize();
	void initialize();

private:
	int _width, _height;
	int _xPos, _yPos;
	int _r, _g, _b, _a;

};