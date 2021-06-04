#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "../QBert/GridComponent.h"
#include "../QBert/BlockComponent.h"
using namespace GameEngine;
PlayerComponent::~PlayerComponent() {};
PlayerComponent::PlayerComponent(std::shared_ptr<GameObject> parent,std::weak_ptr<GameObject> grid, int lives) : BaseComponent(parent)
	,m_Lives{lives}
	,m_pGrid{grid}
	,m_CurrentPos{0,0}
	,m_maxMoveCooldown{0.4f}
{
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(0,0);
	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);

	m_moveCooldown = 0.f;
}
void PlayerComponent::Update(float elapsedSec)
{
	if (m_moveCooldown >= 0.f)
		m_moveCooldown -= elapsedSec;
}
void PlayerComponent::Kill()
{
	m_Lives--;
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(0, 0);

	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);

	m_CurrentPos = { 0,0 };
	
	if (m_Lives == 0)
	{
		m_pParent.lock()->SetIsActive(false); //player is fully dead TODO: reset game or go to some sort of main menu
	}
}

void PlayerComponent::Move(const IPoint2& moveDirection)
{
	if (m_moveCooldown > 0.f)
		return;

	std::cout << moveDirection.x << " , " << moveDirection.y << std::endl;
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	int layers = tempGrid.lock()->GetLayers()-1;
	if (!m_pGrid.expired() && !tempGrid.expired())
	{
		m_CurrentPos.x += moveDirection.x;
		m_CurrentPos.y += moveDirection.y;
		
		if (m_CurrentPos.x < 0 || m_CurrentPos.y < 0 || m_CurrentPos.y > layers) //player kills himself by walking of the array
			Kill();
		
		if (tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y).expired()) //player walks of field
		{
			Kill();
		}

		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);
		
		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x,newPos.y - tempGrid.lock()->GetGridOffsets().y);
		tempGrid.lock()->NotifyGridblockActivate(m_CurrentPos, 0);

		m_moveCooldown = m_maxMoveCooldown;
	}

}

