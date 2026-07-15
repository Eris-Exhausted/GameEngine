#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "EngineMath.h"

namespace nu
{
    void Actor::Update(float dt)
    {
        m_transform.position += (m_vel * dt);

        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        renderer.DrawModel(m_model, m_transform);
    }
}