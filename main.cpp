#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>

using namespace std;

const Uint32 fps = 60; //Set speed in fps (frames per second)
const Uint32 minframetime = 1000 / fps;

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Linear Regressions", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN); //Display window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //Create renderer

    SDL_SetWindowFullscreen(window, 0);

    bool running = true;
    Uint32 frametime;
    SDL_Event event;

    while (running) //This is called once per frame
    {
    	SDL_SetRenderDrawColor(renderer, 143, 143, 143, 255); //Set background color

        SDL_RenderClear(renderer); //Clear screen

        static bool fullScreen = true; //Is fullscreen
        static int windowWidth = 1000; 	//Get window width
        static int windowHeight = 700; //Get window height
        static int screenWidth = 1920;
        static int screenHeight = 1080;
        static int i = 0;
        float posX[1024], posY[1024];
        int x, y;
        float lineX1, lineY1, lineX2, lineY2;
        float m = 1;
        float b = 0;
        float XSum, YSum, XMean, YMean = 0;
        float num = 0;
        float den = 0;
        float length = 0;

        const Uint8* state = SDL_GetKeyboardState(NULL); //Store key state in variable

        SDL_GetMouseState(&x, &y);

        SDL_Rect rect;
        
        for (int n = 0; posX[n] != 0; n++) {
            length++;
        }

        for (int n = 0; n < length; n++) {
            rect.x = posX[n] - 5;
            rect.y = posY[n] - 5;
            cout << posY[n] << endl;
            rect.w = 10;
            rect.h = 10;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        XSum = 0;
        YSum = 0;

        for (int n = 0; n < length; n++) {
            XSum += posX[n];
            YSum += posY[n];
        }

        XMean = XSum / length;
        YMean = YSum / length;

        for (int n = 0; n < length; n++) {
            int numX = posX[n];
            int numY = posY[n];
            num += (numX - XMean) * (numY - YMean);
            den += (numX - XMean) * (numX - XMean);
        }

        m = num / den;
        b = YMean - m * XMean;

        lineX1 = 0;
        lineX2 = 700;
        lineY1 = b;
        lineY2 = (m * 700) + b;

        SDL_RenderDrawLine(renderer, lineX1, lineY1, lineX2, lineY2);
 
        SDL_RenderPresent(renderer); //Render everything
        
        frametime = SDL_GetTicks(); //Get frame time

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        posX[i] = x;
                        posY[i] = y;
                        i++;
                    }
            }
        }

        if (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type) //Detect if user presses the x button
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);

                break; //Quit game
            }
        }

        if (SDL_GetTicks() - frametime < minframetime) //Check if it is running at the right speed
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));

    }

	return 0;
} 