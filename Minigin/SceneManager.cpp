#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace GameEngine;
void SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	m_CurrentScene->Render();
}
void SceneManager::SetCurrentScene(const std::string& sceneName)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [sceneName](const std::shared_ptr<Scene>& s1) {return s1.get()->GetName() == sceneName; });
	if (it != m_Scenes.end())
	{
		m_CurrentScene = *it;
	}
	else
		std::cout << "Scene doesn't exist !";
}
std::weak_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}
Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	if (m_CurrentScene == nullptr)
		m_CurrentScene = scene;
	return *scene;
}
