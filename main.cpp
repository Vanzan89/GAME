#include <iostream>
#include <vector>
#include <SDL.h>
#include <math.h>
#include "constants.cpp"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <time.h>
using namespace std;

int main(int argc, char* args[])
{
	srand(time(NULL));
	  SDL_Window     *window;

	  SDL_Init(SDL_INIT_VIDEO);

	  window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ww, wh, 0);

	  if(window==NULL)
	  {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	  }


	  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	  if (renderer == nullptr) {
		  std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		  return 1;
	  }

	  std::vector<Asteroid> asteroids;

	  PlayerShip player(renderer);

	  for (int i = 0; i < 10; i++) {
		  Asteroid ast(renderer);
		  asteroids.push_back(ast);
	  }

	  std::vector<Bullet*> bullets;
	  for (int i = 0; i < 100; i++) {
		  Bullet *bullet = new Bullet(renderer);
		  bullets.push_back(bullet);
	  }

	  player.SetBulletPool(&bullets);

	  bool running = true;

	  while (running) {

		  SDL_Event event;
		  while (SDL_PollEvent(&event)) {
			  switch (event.type) {
			  case SDL_QUIT:
				  running = false;
				  break;
			 /* default:
				  cout << event.type << "\n";
				  break;
			*/
			  }
		  }


		  player.Update();
		  for (int i = 0; i < asteroids.size(); i++) {
			  asteroids[i].Update();
		  }
		  for (int i = 0; i < bullets.size(); i++) {
			  if (!bullets[i]->active) {
				  continue;
			  }
			  bullets[i]->Update();
		  }
		  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		  SDL_RenderClear(renderer);
		  player.Draw(renderer);
		  for (int i = 0; i < asteroids.size(); i++) {
			  asteroids[i].Draw(renderer);
		  }
		  for (int i = 0; i < bullets.size(); i++) {
			  if (!bullets[i]->active) {
				  continue;
			  }
			  bullets[i]->Draw(renderer);
		  }


		
		  SDL_RenderPresent(renderer);
	  }

	  SDL_DestroyWindow(window);

	  SDL_Quit();

	return 0;
}

//Нарисовать астероид, который рандомно создается и рандомно двигается