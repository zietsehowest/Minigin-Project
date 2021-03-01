#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
dae::PlayerComponent::~PlayerComponent() {};
dae::PlayerComponent::PlayerComponent(std::shared_ptr<GameObject> parent, int lives) : BaseComponent(parent)
	,m_Lives{lives}
{
}
void dae::PlayerComponent::Update(float)
{
	
}
void dae::PlayerComponent::Kill()
{
	m_Lives--;
	if (m_Lives == 0)
	{
		m_pParent.lock()->SetIsActive(false);
	}
}
