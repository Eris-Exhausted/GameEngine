#include "Engine.h"

#include <iostream>
#include <vector>

// Random comment

using namespace nu;

struct Transform
{
    Vector2 position;
    float roation;
    float scale;
};

class Actor
{
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{ transform } {};

    void Update(float dt)
    {
        m_transform.position += (m_vel * dt);

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer) const
    {
        renderer.SetColorInt(255, 255, 255);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform; };
    void SetPosition(const Vector2& position) { m_transform.position = position; };
    void SetRotation(float roation) { m_transform.roation = roation; };
    void SetScale(float scale) { m_transform.scale = scale; };

    Vector2& GetVelocity() { return m_vel; };
    void SetVelocity(const Vector2& velocity) { m_vel = velocity; };

protected :
    Transform m_transform;
    Vector2 m_vel{ 0,0 };
};

int main()
{
    
    // INITIALIZATION
    nu::Renderer renderer;
    float screenSizeX = 1280.0f;
    float screenSizeY = 1024.0f;
    renderer.Initialize("Game Engine", screenSizeX, screenSizeY);

    Input input;
    input.Initialize();

    Time time;

    Vector2 pos(640, 512);
    float speed = 800.0f;
    Vector2 vel(0.0f, 0.0f);

    std::vector<nu::Vector2> points;
    Actor player{ Transform{Vector2{640.0f, 512.0f}, 0.0f, 50.0f} };

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
        input.Update();
        time.Tick();


        //This is the code for adding a single point per button press
        //Left it commented it out since the ButtonDown code does effectively the same thing

       /* if (input.GetButtonPressed(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePos());
        }*/

        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty()) {
                points.push_back(input.GetMousePos());
                
            }
            else {
                Vector2 v = points.back() - input.GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(input.GetMousePos());
                }
            }
        }


        Vector2 force(0.0f, 0.0f);

        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        /*vel += (force * time.GetDeltaTime());
        pos += (vel * time.GetDeltaTime());

        pos.x = Wrap(0.0f, screenSizeX, pos.x);
        pos.y = Wrap(0.0f, screenSizeY, pos.y);*/

        // RENDER
        renderer.SetColorInt(0, 0, 0);
        renderer.Clear();

        for (size_t i = 1; i < points.size(); i++) {
            //renderer.SetColorInt(nu::RandInt(256), nu::RandInt(256), nu::RandInt(256));
            renderer.SetColorInt(0, 0, 255);

            renderer.DrawLine(points[i].x, points[i].y, points[i-1].x, points[i-1].y);
        }

        player.Draw(renderer);
        // character
        //renderer.SetColorInt(255, 255, 255);
        //renderer.DrawFillRect(pos.x - 20, pos.y - 20, 40, 40);
        //renderer.DrawFillRect(input.GetMousePos().x - 20, input.GetMousePos().y - 20, 40, 40);

        renderer.Present();
    }

    // SHUTDOWN
    renderer.ShutDown();

    return 0;
}