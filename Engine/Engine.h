#pragma once

#include "Renderer.h"
#include "Input.h"

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "GameTime.h"
#include "EngineMath.h"

#include "Transform.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"

namespace nu
{
    class Engine {
    public:
        Engine() = default;

        bool Initialize(int resolution_x = 1280, int resolution_y = 720);
        void Shutdown();

        void Update();

        Input& GetInput() { return m_input; }
        Renderer& GetRenderer() { return m_renderer; }
        Time& GetTime() { return m_time; }

    private:
        Input m_input;
        Renderer m_renderer;
        Time m_time;
    };

    extern Engine engine;
}