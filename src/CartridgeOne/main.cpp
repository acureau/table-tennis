#include "Game.h"

int main(int argc, char* argv[]) {
	// Frame limiting variables.
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	// Initialize game object.
	Game* game = new Game;
	game->initialize("Table Tennis", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, (SDL_WINDOW_RESIZABLE));
	
	while (game->isRunning()) {
		// Get ticks at start of loop.
		frameStart = SDL_GetTicks();

		// Do game loop operations.
		game->eventHandler();
		game->update();
		game->render();

		// Frame limiting.
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return(0);
}