#include "Bullet.h"
#include <iostream>

Bullet::Bullet(SDL_Renderer *renderer)
{
	coords = { 200, 200 };
	sourceRect = { 0, 0, width, height };
	destRect = { 0, 0, width, height };
	rotationCenter = { width / 2, height / 2 };

	SDL_Surface* surface = SDL_LoadBMP("laser-blast.bmp");
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "laser-blast.bmp", SDL_GetError());
		throw 1;
	}
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr) {
		printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		throw 1;
	}
}

Bullet::~Bullet()
{
}

void Bullet::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopyEx(renderer, tex, &sourceRect, &destRect, angle, &rotationCenter, SDL_FLIP_NONE);
}

void Bullet::Update()
{
	move();
	handleBorderLimits();
}

void Bullet::move() {
	coords.x += speed * sin(angle * (PI / 180.0));
	coords.y -= speed * cos(angle * (PI / 180.0));

	destRect.x = (int)coords.x - width / 2;
	destRect.y = (int)coords.y - height / 2;
}

void Bullet::handleBorderLimits()
{
	if (coords.y + height < -10 || 
		coords.y > wh + 10 || 
		coords.x > ww + 10 ||
		coords.x + width < -10
	) {
		active = false;
	}
}