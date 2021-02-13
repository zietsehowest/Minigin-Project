#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextComponent.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{
	for (auto component : m_Components)
	{
		component.second->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component.second->Render(m_Transform);
	}
}
std::map<dae::ComponentType, std::shared_ptr<dae::BaseComponent>> dae::GameObject::GetComponents() const
{
	return m_Components;
}
void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

bool dae::GameObject::AddComponent(const ComponentType& type)
{
	auto it = std::find_if(m_Components.begin(), m_Components.end(), [type](const std::pair<ComponentType, std::shared_ptr <BaseComponent>>& c)
		{
			return type == c.first;
		});
	if (it != m_Components.end())
		return false;
	else
	{
		switch (type)
		{
		case ComponentType::render:
			m_Components[type] = std::make_shared<RenderComponent>();
			break;
		case ComponentType::text:
			m_Components[type] = std::make_shared<TextComponent>();
		}
		
	}
	return true;
}

