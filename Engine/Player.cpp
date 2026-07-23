#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"

namespace nu
{
	void Player::Update(float dt) {

		Vector2 force = Vector2(0, 0);
		
		float thrust = 0.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -m_speed;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = m_speed;

		float rotate = 0.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -m_speed;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = m_speed;
		SetVelocity(GetVelocity() + force * Engine::Get().GetTime().GetDeltaTime());

		SetRotation(m_transform.roation + rotate * dt);
		Vector2 velocity{ 1,0 };

		Actor::Update(dt);
		
	}

	void Player::Draw(const Renderer& renderer) const {
		Actor::Draw(renderer);
	}
}
