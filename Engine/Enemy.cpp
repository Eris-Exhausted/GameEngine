#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"

namespace nu
{
	Input input;
	void Enemy::Update(float dt) {
		float thrust = 0.0f;
		if (input.GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
		if (input.GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

		float rotate = 0.0f;
		if (input.GetKeyDown(SDL_SCANCODE_W)) rotate = 180.0f;
		if (input.GetKeyDown(SDL_SCANCODE_S)) rotate = -180.0f;

		SetRotation(m_transform.roation + rotate * dt);
		Vector2 velocity{ 1,0 };

		SetVelocity(GetVelocity() + GetVelocity() * dt);

		Actor::Update(dt);
		
	}

	void Enemy::Draw(const Renderer& renderer) const {
		Actor::Draw(renderer);
	}
}
