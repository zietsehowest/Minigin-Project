#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace GameEngine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
	
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),[](std::shared_ptr<GameObject>& s) {return !s->GetIsActive(); }), m_Objects.end());
}

void Scene::Render()
{
	 sort(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& go1, const std::shared_ptr<GameObject>& go2) {return go1->GetRenderPriority() > go2->GetRenderPriority(); });

	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

