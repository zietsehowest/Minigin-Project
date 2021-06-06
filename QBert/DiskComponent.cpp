#include "DiskComponent.h"
#include "PlayerComponent.h"
using namespace GameEngine;
DiskComponent::DiskComponent(std::shared_ptr<GameObject> parent,IPoint2 DiskCoordinates, float teleportCooldown) : BaseComponent(parent)
	,m_IsDiskActivated{false}
	,m_TeleportCooldown{ teleportCooldown }
	,m_Position{DiskCoordinates}
{

}
void GameEngine::DiskComponent::ActivateDisk(std::weak_ptr<GameObject> qbert)
{
	m_IsDiskActivated = true;
	qbert.lock()->SetPosition(m_pParent.lock()->GetTransform().GetPosition().x, m_pParent.lock()->GetTransform().GetPosition().y - 20); //put qbert on 
	m_Qbert = qbert;
}
void GameEngine::DiskComponent::Update(float elapsedSec)
{
	if (m_IsDiskActivated)
	{
		m_TeleportCooldown -= elapsedSec;
		if (m_TeleportCooldown <= 0.f)
		{
			m_Qbert.lock()->GetComponent<PlayerComponent>().lock()->MoveTopPosition();
			m_pParent.lock()->SetIsActive(false); //remove elevator
		}
	}

}
