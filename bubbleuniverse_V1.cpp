#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <math.h>

using namespace std;

SDL_Window* window = SDL_CreateWindow("Bubble Universe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1600,880,0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

int Iter = 256+128;
float D = 56;
float R = D*((2*M_PI)/360);
float th = cos(R);
float r = sin(R);
float u = 0;
float v = 0;
float x = 0;
float t = 0;
float scale = 220;

float minC = 0.0;
float maxC = 255.0;

void clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void setPixel(int X, int Y, Uint8 r=255 ,Uint8 g=255 ,Uint8 b=255 ,Uint8 a=255) {
	SDL_SetRenderDrawColor(renderer ,r, g, b, a);
	SDL_RenderDrawPoint(renderer, X, Y);
}

int main() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	if (!window) {
		SDL_Quit();
		return -1;
	}

	SDL_Event event;
	while(true) {
		clearScreen();

		for(int i = 0; i<Iter+1; i++) {
			for(int j = 0; j<Iter+1; j++) {
				float A = i*2*(M_PI/235)+u+t;
				float B = i+v+t;
				u = sin(A) + sin(B);
				v = cos(A) + cos(B);
				float Red = i;
				float Green = j/2;
				float Blue = std::min(std::max(((512-Red-Green)/2),minC),maxC);
				setPixel((u*scale)+800, (v*scale)+450, Red, Green, Blue);
			}
		}
		t += 0.0025;
		//SDL_Delay(1000/60);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);
				SDL_Quit();
				return 0;
			}
		}
	}
}