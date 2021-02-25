#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{
	for (auto component : m_Components)
	{
		component->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component->Render(m_Transform);
	}
}
std::vector<std::shared_ptr<dae::BaseComponent>> dae::GameObject::GetComponents() const
{
	return m_Components;
}
void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

