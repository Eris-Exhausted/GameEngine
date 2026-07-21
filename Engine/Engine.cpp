#include "pch.h"
#include "framework.h"
#include "engine.h"

#include <iostream>


namespace nu
{
    Engine engine;

    bool Engine::Initialize(int resolution_x, int resolution_y) {
        m_input.Initialize();
        m_renderer.Initialize("Game Engine", resolution_x, resolution_y);
        return true;
    }

    void Engine::Shutdown() {
        m_input.Shutdown();
        m_renderer.Shutdown();
    }

    void Engine::Update() {
        m_input.Update();
        m_time.Tick();
    }
}