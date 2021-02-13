#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
dae::RenderComponent::~RenderComponent()
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