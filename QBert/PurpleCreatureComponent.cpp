#include "PurpleCreatureComponent.h"
#include "GameObject.h"
#include "../QBert/GridComponent.h"
#include "../QBert/BlockComponent.h"
#include "RenderComponent.h"
using namespace GameEngine;
PurpleCreatureComponent::~PurpleCreatureComponent() {};
PurpleCreatureComponent::PurpleCreatureComponent(std::shared_ptr<GameObject> parent, std::weak_ptr<GameObject> grid, const EnemyType& type,const std::vector<std::string>& texturePaths) : BaseComponent(parent)
	,m_pGrid{grid}
	,m_Type{type}
	,m_maxMoveCooldown{1.4f}
	,m_HeightOffset{15.f}
{
	m_pParent.lock()->GetComponent<RenderComponent>().lock()->SetTexture(texturePaths[int(type)]);

	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	auto bottomLine = tempGrid.lock()->GetLayers()-1;
	if (type == EnemyType::wrongway) //starts left
	{
		m_CurrentPos = { 0,bottomLine };
		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(0, bottomLine);
		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x - tempGrid.lock()->GetGridOffsets().x,newPos.y + m_HeightOffset);
	}
	else //starts right
	{
		m_CurrentPos = { bottomLine,bottomLine };
		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(bottomLine, bottomLine);
		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x + tempGrid.lock()->GetGridOffsets().x,newPos.y + m_HeightOffset);
	}

	m_moveCooldown = m_maxMoveCooldown;
}
void PurpleCreatureComponent::Update(float elapsedSec)
{
	if (m_moveCooldown >= 0.f)
		m_moveCooldown -= elapsedSec;
	else
		Move();
}
void PurpleCreatureComponent::Kill()
{
	m_pParent.lock()->SetIsActive(false);
}
void PurpleCreatureComponent::Move()
{
	m_moveCooldown = m_maxMoveCooldown;
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	if (m_CurrentPos.y == 0)
	{
		Kill();
		return;
	}
	if (m_Type == EnemyType::wrongway)
	{
		int randomDirection = rand() % 2;
		IPoint2 movement{ 0,0 };
		randomDirection == 0 ? movement = { 0,-1 } : movement = {1,0};
		
		m_CurrentPos.x += movement.x;
		m_CurrentPos.y += movement.y;

		if (m_CurrentPos.x > m_CurrentPos.y)
		{
			Kill();
			return;
		}
		
		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);
		
		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x - tempGrid.lock()->GetGridOffsets().x, newPos.y + m_HeightOffset);
	}
	else
	{
		int randomDirection = rand() % 2;
		IPoint2 movement{ 0,0 };
		randomDirection == 0 ? movement = { -1,-1 } : movement = { -1,0 };

		m_CurrentPos.x += movement.x;
		m_CurrentPos.y += movement.y;

		if (m_CurrentPos.x < 0)
		{
			Kill();
			return;
		}

		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x + tempGrid.lock()->GetGridOffsets().x, newPos.y + m_HeightOffset);
	}

}