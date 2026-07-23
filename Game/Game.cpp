#include "Engine.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>
#include "Assets.h"

#define ENGINE Engine::Get()

using namespace nu;

int main()
{

    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // INITIALIZATION
    ENGINE.Initialize();

    nu::Renderer renderer;
    float screenSizeX = 1280.0f;
    float screenSizeY = 1024.0f;
    renderer.Initialize("Game Engine", screenSizeX, screenSizeY);

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    /*Input input;
    input.Initialize();*/

    Time time;

    Mesh ship(std::vector<Vector2>{Vector2(-3, -2), Vector2(2, 0), Vector2(-3, 2), Vector2(-1.5, 0), Vector2(-3, -2)},
        Vector3{ 255,255,255 });
    Mesh flame(std::vector<Vector2>{Vector2(-4, -0), Vector2(-5, 1), Vector2(-7, 0), Vector2(-5, -1), Vector2(-4,0)},
        Vector3{ 255,0,0 });
    Mesh enemyShip(std::vector<Vector2>{Vector2(-2, -1), Vector2(1, 0), Vector2(-2, 1), Vector2(-2, -1)},
        Vector3{ 255,0,0 });

    Model playerModel;
    Model enemyModel;
    playerModel.AddMesh(ship);
    playerModel.AddMesh(flame);
    enemyModel.AddMesh(enemyShip);

    Vector2 pos(640, 512);
    float speed = 800.0f;
    Vector2 vel(0.0f, 0.0f);

    std::vector<nu::Vector2> points;
    Scene scene;

    Player* player = new Player(2000.0f, Transform{ Vector2{640.0f, 512.0f}, 0.0f, 10.0f }, playerModel);
    Enemy* enemy = new Enemy(2000.0f, Transform{ Vector2{640.0f, 512.0f}, 0.0f, 10.0f }, enemyModel);
    scene.AddActor(enemy);
    scene.AddActor(player);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->playSound(sounds[5], 0, false, nullptr);


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

        // engine
        //input.Update();
        time.Tick();
        ENGINE.Update();
        audio->update();


        if (ENGINE.GetInput().GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty()) {
                points.push_back(ENGINE.GetInput().GetMousePos());

            }
            else {
                Vector2 v = points.back() - ENGINE.GetInput().GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(ENGINE.GetInput().GetMousePos());
                }
            }
        }


        Vector2 force(0.0f, 0.0f);

        if (ENGINE.GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (ENGINE.GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = speed;
        if (ENGINE.GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = speed;
        if (ENGINE.GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;

        if (ENGINE.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }
        if (ENGINE.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (ENGINE.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (ENGINE.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (ENGINE.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        scene.Update(ENGINE.GetTime().GetDeltaTime());

        // RENDER
        renderer.SetColorInt(0, 0, 0);
        renderer.Clear();

        for (size_t i = 1; i < points.size(); i++) {
            //renderer.SetColorInt(nu::RandInt(256), nu::RandInt(256), nu::RandInt(256));
            renderer.SetColorInt(0, 0, 255);

            renderer.DrawLine(points[i].x, points[i].y, points[i - 1].x, points[i - 1].y);
        }

        scene.Draw(renderer);

        renderer.Present();
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}