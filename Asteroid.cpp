#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(SDL_Renderer *renderer)
{
	int x = rand() % ww;
	int y = rand() % wh;
	coords = { (double) x - width / 2,  (double)y - height / 2 };
	sourceRect = { 0, 0, width, height };
	destRect = { (int)coords.x, (int)coords.y, width, height };
	rotationCenter = { width / 2, height / 2 };
	angle = (double) (rand() % 360);
	if (rand() % 100 + 1 > 50) {
		animationType = 1;
		currentFrame = 32;
	}
	else {
		animationType = 0;
		currentFrame = 0;
	}
	animationSpeed = rand() % 30 + 20;

	speed = (rand() % 20 + 10) / 10;

	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	lastFrameChanged = ms;

	SDL_Surface* surface = SDL_LoadBMP("asteroid.bmp");
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "spaceship.bmp", SDL_GetError());
		throw 1;
	}
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr) {
		printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		throw 1;
	}
}

Asteroid::~Asteroid()
{
}

void Asteroid::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopyEx(renderer, tex, &sourceRect, &destRect, angle, &rotationCenter, SDL_FLIP_NONE);
}

void Asteroid::Update()
{
	animate();
	move();
	handleBorderLimits();
}

void Asteroid::animate()
{
	milliseconds now = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	if (milliseconds(lastFrameChanged).count() + animationSpeed > milliseconds(now).count()) {
		return;
	}

	int x = (currentFrame % columns) * width;
	int y = (currentFrame / columns) * height;

	sourceRect.x = x;
	sourceRect.y = y;

	currentFrame++;

	if (currentFrame > totalFrames * (animationType + 1) - 1) {
		currentFrame = animationType == 0 ? 0 : 32;
	}

	lastFrameChanged = now;
}

void Asteroid::move() {
	coords.x += speed * sin(angle * (PI / 180.0));
	coords.y -= speed * cos(angle * (PI / 180.0));

	destRect.x = (int)coords.x - width / 2;
	destRect.y = (int)coords.y - height / 2;
}

void Asteroid::handleBorderLimits()
{
	// Up
	if (coords.y + height < -10) {
		coords.y = wh;
	}

	// Down
	else if (coords.y > wh + 10) {
		coords.y = -height;
	}

	// Right
	if (coords.x > ww + 10) {
		coords.x = -width;
	}

	// Left
	else if (coords.x + width < -10) {
		coords.x = ww;
	}
}
