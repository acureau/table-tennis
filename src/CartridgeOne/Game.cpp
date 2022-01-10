#include "Game.h"
#include "Paddle.h"
#include "Net.h"
#include "Ball.h"

// Declare game objects.
Paddle* leftPaddle;
Paddle* rightPaddle;
Net* net;
Ball* ball;

// Game deconstructor.
Game::~Game() { clean(); }

void Game::initialize(const char* title, int xPos, int yPos, int width, int height, Uint32 flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		gameWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		SDL_SetWindowPosition(gameWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		if (gameWindow) {
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
			if (gameRenderer) {
				running = true;
			}
			else {
				std::cout << "SDL failed initial render." << std::endl;
				running = false;
			}
		}
		else {
			std::cout << "SDL failed to create window." << std::endl;
			running = false;
		}
	}
	else {
		std::cout << "SDL failed to initialize." << std::endl;
		running = false;
	}

	// Initialize Objects
	leftPaddle = new Paddle(*this);
	leftPaddle->initialize('L');

	rightPaddle = new Paddle(*this);
	rightPaddle->initialize('R');

	net = new Net(*this);
	net->initialize();

	ball = new Ball(*this);
	ball->initialize();
}

void Game::update() {
	// Process paddle inputs, apply physics to paddles.
	leftPaddle->processInput('L');
	leftPaddle->physicsUpdate('L');
	rightPaddle->processInput('R');
	rightPaddle->physicsUpdate('R');

	// Process ball input, check ball collision, move ball.
	ball->processInput(leftPaddle, rightPaddle);
	ball->checkCollision(leftPaddle, rightPaddle);
	ball->move();

	// Process net input.
	net->processInput();
}

void Game::resize() {
	leftPaddle->resize('L');
	rightPaddle->resize('R');
	net->resize();
	ball->resize();
}

void Game::render() {
	// Set the screen color.
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);

	// Render the left paddle.
	leftPaddle->renderPaddle();

	// Render the right paddle.
	rightPaddle->renderPaddle();

	// Render the net.
	net->renderNet();

	// Render the ball.
	ball->renderBall();

	// Display the final render.
	SDL_RenderPresent(gameRenderer);
}

void Game::clean() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	SDL_Quit();
}

void Game::eventHandler() {
	SDL_Event gameEvent;
	SDL_PollEvent(&gameEvent);

	switch (gameEvent.type)
	{
		case SDL_QUIT:
			running = false;
			break;

		case SDL_WINDOWEVENT:
			if (gameEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
				resize();
			}
			break;
	}
}