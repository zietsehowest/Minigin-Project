#include "CoilyComponent.h"
#include "GameObject.h"
#include "../QBert/GridComponent.h"
#include "../QBert/BlockComponent.h"
#include "RenderComponent.h"
#include "PlayerComponent.h"
using namespace GameEngine;
CoilyComponent::~CoilyComponent() {};
CoilyComponent::CoilyComponent(std::shared_ptr<GameObject> parent, std::shared_ptr<GameObject> target, std::weak_ptr<GameObject> grid, const std::string& evolutionTexture) : BaseComponent(parent)
	,m_pGrid{grid}
	,m_CurrentPos{0,0}
	,m_maxMoveCooldown{1.f}
	,m_CoilyState{CoilyState::traverse}
	,m_EvolutionTexture{evolutionTexture}
	,m_pTarget{target}
{
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(0, 1);
	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);

	m_moveCooldown = m_maxMoveCooldown;
}
void CoilyComponent::Update(float elapsedSec)
{
	if (m_moveCooldown >= 0.f)
		m_moveCooldown -= elapsedSec;
	else
		Move();
}
void CoilyComponent::Kill()
{

}
void CoilyComponent::Move()
{
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	int layers = tempGrid.lock()->GetLayers() - 1;
	if (m_CurrentPos.y == layers && m_CoilyState != CoilyState::chase)
	{
		m_pParent.lock()->GetComponent<RenderComponent>().lock()->SetTexture(m_EvolutionTexture);
		m_CoilyState = CoilyState::chase;
	}
	if (m_CoilyState == CoilyState::traverse) //traverse to the bottom
	{
		m_CurrentPos.y += 1;
		auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

		glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
		m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);
	}
	if (m_CoilyState == CoilyState::chase) //chase Qbert
	{
		IPoint2 targetGridPos = m_pTarget.lock()->GetComponent<PlayerComponent>().lock()->GetCurrentGridPos();
		IPoint2 tempMove{0,0};
		if (m_CurrentPos == targetGridPos)
		{
			//do damage and Reset Level 
			return;
		}
		else if (m_CurrentPos.y >= targetGridPos.y)//below target
		{
			if (m_CurrentPos.x < targetGridPos.x) //right so go top right
			{
				tempMove.y = -1;
			}
			else //left so go top left
			{
				tempMove.x = -1;
				tempMove.y = -1;
			}

			m_CurrentPos.x += tempMove.x;
			m_CurrentPos.y += tempMove.y;

			if (m_CurrentPos.x < 0)
				m_CurrentPos.x = 0;

			auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

			glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
			m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);
		}
		else //above target
		{
			if (m_CurrentPos.x < targetGridPos.x) //right so go bottom right
			{
				tempMove.x = 1;
				tempMove.y = 1;
			}
			else //left so go bottom left
			{
				tempMove.y = 1;
			}

			m_CurrentPos.x += tempMove.x;
			m_CurrentPos.y += tempMove.y;


			auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

			glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
			m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);
		}

	}

	m_moveCooldown = m_maxMoveCooldown;
}