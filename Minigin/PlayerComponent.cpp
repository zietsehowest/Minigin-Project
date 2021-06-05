#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "../QBert/GridComponent.h"
#include "../QBert/BlockComponent.h"
#include "StatsComponent.h"
#include "../QBert/DiskComponent.h"
using namespace GameEngine;
PlayerComponent::~PlayerComponent() {};
PlayerComponent::PlayerComponent(std::shared_ptr<GameObject> parent,std::weak_ptr<GameObject> grid) : BaseComponent(parent)
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
	ResetPosition();

	m_pParent.lock()->GetComponent<StatsComponent>().lock()->Attack(); //let the statcomponent know it needs to update the lives including the UI
}
void PlayerComponent::ResetPosition()
{
	m_CurrentPos.x = 0;
	m_CurrentPos.y = 0;

	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);
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
		{
			auto tempLeftDisk = tempGrid.lock()->checkForDisk(m_CurrentPos.y+1, -1);
			if (!tempLeftDisk.expired())
			{
				tempLeftDisk.lock()->GetComponent<DiskComponent>().lock()->ActivateDisk(m_pParent);
				m_moveCooldown = m_maxMoveCooldown;
				return;
				//check if coily is close so yes kill coily and add points
			}
			else
			{
				Kill();
			}
		}
		
		if (tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y).expired()) //player walks of field
		{
			auto tempRightDisk = tempGrid.lock()->checkForDisk(m_CurrentPos.y+1, 1);
			if (!tempRightDisk.expired())
			{
				tempRightDisk.lock()->GetComponent<DiskComponent>().lock()->ActivateDisk(m_pParent);
				m_moveCooldown = m_maxMoveCooldown;
				return;
				//check if coily is close so yes kill coily and add points
			}
			else
			{
				Kill();
			}
			
		}

		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);
		
		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x,newPos.y - tempGrid.lock()->GetGridOffsets().y);
		bool EarnedPoints = tempGrid.lock()->NotifyGridblockToggle(m_CurrentPos, 0,1);
		
		if(EarnedPoints)
			m_pParent.lock()->GetComponent<StatsComponent>().lock()->ChangeScore(50); //let the statcomponent know it needs to update the score including the UI

		m_moveCooldown = m_maxMoveCooldown;
	}

}


