#pragma once
#include <SDL.h>
#include "vector2d.cpp"
#include "constants.cpp"
#include <chrono>

using namespace std::chrono;
class Asteroid
{
private:
	const int width = 64;
	const int height = 64;
	SDL_Texture *tex;
	vector2d coords;
	double angle = 0.0;
	double speed = 0.0;
	SDL_Point rotationCenter;
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	int animationSpeed = 60;
	milliseconds lastFrameChanged;
	int currentFrame = 0;
	const int columns = 8;
	const int totalFrames = 31;
	int animationType;

public:
	Asteroid(SDL_Renderer *renderer);
	~Asteroid();

	void Draw(SDL_Renderer *renderer);
	void Update();

	void animate();
	void move();
	void handleBorderLimits();

};

