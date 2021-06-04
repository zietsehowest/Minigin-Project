#pragma once
#include "Singleton.h"

namespace GameEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		
		void SetCurrentScene(const std::string& sceneName);
		std::weak_ptr<Scene> GetCurrentScene() const;
		
		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_CurrentScene = nullptr;
	};
}
