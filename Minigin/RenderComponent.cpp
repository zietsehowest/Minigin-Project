#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
GameEngine::RenderComponent::~RenderComponent(){}
GameEngine::RenderComponent::RenderComponent(std::shared_ptr<GameObject> parent) : BaseComponent(parent)
{

}
void GameEngine::RenderComponent::Update(float) {};
void GameEngine::RenderComponent::Render(const Transform& transform) const
{
	const auto pos = transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
void GameEngine::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}