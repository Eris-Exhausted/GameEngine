#pragma once
#include <vector>


namespace nu
{
	class Actor;

	class Scene
	{
	public:
		void AddActor(Actor* actor);

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		/*template<typename T>
		T* GetActorByName(const std::string& name);*/

		private:
			std::vector<Actor*> m_actors;
	};

	// Make names and stuff actually work
	// so player can get other actors in the scene and vice versa
	// Cause I'm really fucking tired of trying to follow whatever maple is doing

	/*template<typename T>
	inline T* GetActorByName(const std::string& name)
	{
		for (auto actor : m_actors)
		{
			T* actorT = dynamic_case<T*>(actor);
			if (actorT && actorT->m_name == name)
			{
				return actorT;
			}
		}
		return nullptr;
	}*/
}