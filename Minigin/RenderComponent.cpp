#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
dae::RenderComponent::~RenderComponent(){}
dae::RenderComponent::RenderComponent(std::shared_ptr<GameObject> parent) : BaseComponent(parent)
{

}
void dae::RenderComponent::Update(float) {};
void dae::RenderComponent::Render(const Transform& transform) const
{
	const auto pos = transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}