#include "PlayerShip.h"
#include <iostream>



PlayerShip::PlayerShip(SDL_Renderer *renderer)
{
	coords = { (double) ww / 2,  (double) wh / 2 };
	sourceRect = { 0, 0, width, height };
	destRect = { (int) coords.x, (int) coords.y, width, height };
	rotationCenter = { width / 2, height / 2 };

	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	lastShotAt = ms;

	SDL_Surface* spaceship = SDL_LoadBMP("spaceship.bmp");
	if (spaceship == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "spaceship.bmp", SDL_GetError());
		throw 1;
	}
	tex = SDL_CreateTextureFromSurface(renderer, spaceship);
	SDL_FreeSurface(spaceship);
	if (tex == nullptr) {
		printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		throw 1;
	}
}


PlayerShip::~PlayerShip()
{
}

void PlayerShip::Draw(SDL_Renderer *renderer) {
	SDL_RenderCopyEx(renderer, tex, &sourceRect, &destRect, angle, &rotationCenter, SDL_FLIP_NONE);
}

void PlayerShip::Update() {
	
	handleMovementInput();
	handleShootingInput();
	handleBorderLimits();
	calculateMovement();
}

void PlayerShip::SetBulletPool(std::vector<Bullet*> *bulletPool)
{
	this->bulletPool = bulletPool;
}

void PlayerShip::handleMovementInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RIGHT]) {
		angle += rotationSpeed;
	}
	if (state[SDL_SCANCODE_LEFT]) {
		angle -= rotationSpeed;
	}
	if (state[SDL_SCANCODE_UP]) {
		speed += acc;
		if (speed >= speedLimit) {
			speed = speedLimit;
		}
	}
	else {
		if (speed > 0) {
			speed -= acc;
		}

	}

	if (state[SDL_SCANCODE_DOWN]) {
		speed -= acc * 2;
	}

	if (speed < 0) {
		speed = 0;
	}
}

void PlayerShip::handleShootingInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (!state[SDL_SCANCODE_SPACE]) {
		return;		
	}

	milliseconds now = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	if (milliseconds(lastShotAt).count() + bulletRechargeTime > milliseconds(now).count()) {
		return;
	}

	Bullet *bullet = NULL;
	for (int i = 0; i < bulletPool->size(); i++) {
		if (!bulletPool->at(i)->active) {
			bullet = bulletPool->at(i);
			break;
		}
	}

	if (bullet != NULL) {
		bullet->active = true;
		bullet->coords.x = coords.x + 55 * sin(angle * (PI / 180.0));
		bullet->coords.y = coords.y - 55 * cos(angle * (PI / 180.0));
		bullet->angle = angle;
	}

	lastShotAt = now;
}

void PlayerShip::calculateMovement()
{
	if (speed != 0) {
		coords.x += speed * sin(angle * (PI / 180.0));
		coords.y -= speed * cos(angle * (PI / 180.0));
	}

	destRect.x = (int)coords.x - width / 2;
	destRect.y = (int)coords.y - height / 2;
}

void PlayerShip::handleBorderLimits()
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

