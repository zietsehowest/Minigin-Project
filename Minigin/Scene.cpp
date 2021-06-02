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
	auto temp = std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<GameObject>& s) {

		if (s->GetIsActive())
		{
			return false;
		}
		else
			return true;
		});
	if (temp != m_Objects.end())
	{
		m_Objects.erase(temp, m_Objects.end());
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

