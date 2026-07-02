#include "Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

// Random comment

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
        for (int i = 0; i < 1000; i++) {
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }

        renderer.SetColor(0, 255, 0);
        renderer.DrawFillRect(270, 190, 200, 200);

        renderer.SetColor(255, 255, 255);

        //SDL_RenderDebugText(renderer, 10, 10, "Hello World");

        renderer.Present();
    }

    renderer.ShutDown();

    return 0;
}