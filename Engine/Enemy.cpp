#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"

namespace nu
{
	void Enemy::Update(float dt) {

		Vector2 force = Vector2(0, 0);

		float thrust = 0.0f;

		float rotate = 0.0f;

		SetVelocity(GetVelocity() + force * engine.GetTime().GetDeltaTime());

		SetRotation(m_transform.roation + rotate * dt);
		Vector2 velocity{ 1,0 };

		Actor::Update(dt);

	}

	void Enemy::Draw(const Renderer& renderer) const {
		Actor::Draw(renderer);
	}
}
