#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<SceneObject>& s) {
		auto gameObjectCast = std::dynamic_pointer_cast<GameObject>(s);
		if (gameObjectCast == nullptr)
		{
			return false;
		}
		if (!gameObjectCast->GetIsActive())
		{
			return true;
		}
		else
			return false;
		}));
	
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

