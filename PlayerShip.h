#pragma once
#include <SDL.h>
#include "vector2d.cpp"
#include "constants.cpp"
#include <chrono>
#include <vector>
#include "Bullet.h"

using namespace std::chrono;
class PlayerShip
{
private:
	const int width = 106;
	const int height = 93;
	SDL_Texture *tex;
	vector2d coords;
	double angle = 0.0;
	const double rotationSpeed = 3.0;
	double speed = 0.0;
	const double acc = 0.05;
	const double speedLimit = 8;
	SDL_Point rotationCenter;
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	milliseconds lastShotAt;
	int bulletRechargeTime = 150;

	std::vector<Bullet*> *bulletPool;

	void handleMovementInput();
	void handleShootingInput();
	void calculateMovement();
	void handleBorderLimits();
public:
	PlayerShip(SDL_Renderer *renderer);
	~PlayerShip();

	void Draw(SDL_Renderer *renderer);
	void Update();

	void SetBulletPool(std::vector<Bullet*> *bulletPool);
};

