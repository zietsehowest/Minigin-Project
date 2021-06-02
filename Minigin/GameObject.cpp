#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::Update(float elapsedSec)
{
	for (auto component : m_Components)
	{
		component->Update(elapsedSec);
	}
}

void GameEngine::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component->Render(m_Transform);
	}
}
std::vector<std::shared_ptr<GameEngine::BaseComponent>> GameEngine::GameObject::GetComponents() const
{
	return m_Components;
}
void GameEngine::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

