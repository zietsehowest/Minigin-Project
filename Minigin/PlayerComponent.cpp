#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
GameEngine::PlayerComponent::~PlayerComponent() {};
GameEngine::PlayerComponent::PlayerComponent(std::shared_ptr<GameObject> parent, int lives) : BaseComponent(parent)
	,m_Lives{lives}
{
}
void GameEngine::PlayerComponent::Update(float)
{
	
}
void GameEngine::PlayerComponent::Kill()
{
	m_Lives--;
	if (m_Lives == 0)
	{
		m_pParent.lock()->SetIsActive(false);
	}
}
