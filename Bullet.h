#pragma once
#include <SDL.h>
#include "vector2d.cpp"
#include "constants.cpp"
#include <chrono>

using namespace std::chrono;
class Bullet
{
private:
	const int width = 9;
	const int height = 30;
	SDL_Texture *tex;
	double speed = 10.0;
	SDL_Point rotationCenter;
	SDL_Rect sourceRect;
	SDL_Rect destRect;

public:
	Bullet(SDL_Renderer *renderer);
	~Bullet();

	bool active = false;
	vector2d coords;
	double angle = 0.0;

	void Draw(SDL_Renderer *renderer);
	void Update();
	void handleBorderLimits();

	void move();

};

