#pragma once
#include <SDL.h>
#include <iostream>

class Game {
public:
	// Deconstructor
	~Game();

	// Methods
	void initialize(const char* title, int xPos, int yPos, int width, int height, Uint32 flags);
	void update();
	void render();
	void clean();
	void eventHandler();
	void resize();
	bool isRunning() { return(running); };

private:
	bool running;

protected:
	SDL_Renderer* gameRenderer;
	SDL_Window* gameWindow;

};

