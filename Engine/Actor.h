#pragma once

#include "Transform.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Mesh.h"
#include "Model.h"

namespace nu
{
    class Actor
    {
    public:
        Actor() = default;
        Actor(const Transform& transform) : m_transform{ transform } {};
        Actor(const Transform& transform, const Model& model) :
            m_transform{ transform },
            m_model{ model }
        {}

        virtual void Update(float dt);
        void Draw(const Renderer& renderer) const;

        const Transform& GetTransform() const { return m_transform; };
        void SetPosition(const Vector2& position) { m_transform.position = position; };
        void SetRotation(float roation) { m_transform.roation = roation; };
        void SetScale(float scale) { m_transform.scale = scale; };

        Vector2& GetVelocity() { return m_vel; };
        void SetVelocity(const Vector2& velocity) { m_vel = velocity; };

    protected:
        Transform m_transform;
        Vector2 m_vel{ 0,0 };

        Model m_model;
    };
 }