#include "Engine.h"

#include <iostream>
#include <vector>

// Random comment

using namespace nu;

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    Input input;
    input.Initialize();

    nu::Vector2 vel(0.5f, 0.5f);

    std::vector<nu::Vector2> v;

    for (int i = 0; i < 3000; i++) {
        nu::Vector2 vec{ nu::RandFloat(1920) , nu::RandFloat(1024) };

        v.push_back(vec);
    }

    
    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "Pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "Down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "Released\n";


        // RENDER
        renderer.SetColorInt(0, 0, 0);
        renderer.Clear();

        /*for (int i = 0; i < 10; i++) {
            renderer.SetColorInt(nu::RandInt(256), nu::RandInt(256), nu::RandInt(256));
            renderer.DrawLine(nu::RandFloat(1920), nu::RandFloat(1024), nu::RandFloat(1920), nu::RandFloat(1024));
        }*/

        for (size_t i = 0; i < v.size(); i++) {
            renderer.SetColorInt(nu::RandInt(256), nu::RandInt(256), nu::RandInt(256));

            //v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        renderer.DrawFillRect(input.GetMousePos().x - 20, input.GetMousePos().y - 20, 40, 40);

        /*for (int i = 0; i < 5; i++) {
            renderer.SetColorInt(nu::RandInt(256), nu::RandInt(256), nu::RandInt(256));
            renderer.DrawFillRect(nu::RandFloat(1920), nu::RandFloat(1024), nu::RandFloat(1920), nu::RandFloat(1024));
        }*/

        renderer.SetColorInt(0, 255, 0);

        //SDL_RenderDebugText(renderer, 10, 10, "Hello World");

        renderer.Present();
    }

    // SHUTDOWN
    renderer.ShutDown();

    return 0;
}