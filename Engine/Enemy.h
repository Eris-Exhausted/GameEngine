#pragma once

#include "Actor.h"
#include "Input.h"

namespace nu
{
	class Enemy : public nu::Actor {
	public:
		Enemy() = default;
		Enemy(float speed, const nu::Transform& transform) :
			Actor(transform),
			m_speed(speed)
		{}

		Enemy(float speed, const nu::Transform& transform, const nu::Model& model) :
			Actor(transform, model),
			m_speed(speed)
		{}

		void Update(float dt);
		void Draw(const Renderer& renderer) const;

	private:
		int m_ammo = 0;
		float m_speed = 800.0f;
	};
}
