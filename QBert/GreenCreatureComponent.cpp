#include "GreenCreatureComponent.h"
#include "GameObject.h"
#include "../QBert/GridComponent.h"
#include "../QBert/BlockComponent.h"
#include "RenderComponent.h"
#include "Audio.h"
#include "GameAudio.h"
#include "ServiceLocator.h"
using namespace GameEngine;
GreenCreatureComponent::~GreenCreatureComponent() {};
GreenCreatureComponent::GreenCreatureComponent(std::shared_ptr<GameObject> parent, std::weak_ptr<GameObject> grid, const std::vector<std::string>& texturePaths) : BaseComponent(parent)
	,m_pGrid{grid}
	,m_maxMoveCooldown{1.5f}
{
	int randomTexture = rand()%2;
	m_pParent.lock()->GetComponent<RenderComponent>().lock()->SetTexture(texturePaths[randomTexture]);

	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	m_CurrentPos = { 0,0 };
	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(0, 0);
	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);

	m_moveCooldown = m_maxMoveCooldown;
}
void GreenCreatureComponent::Update(float elapsedSec)
{
	if (m_moveCooldown >= 0.f)
		m_moveCooldown -= elapsedSec;
	else
		Move();
}
void GreenCreatureComponent::Kill()
{
	m_pParent.lock()->SetIsActive(false);
}
void GreenCreatureComponent::Move()
{
	m_moveCooldown = m_maxMoveCooldown;
	auto tempGrid = m_pGrid.lock()->GetComponent<GridComponent>();
	int layers = tempGrid.lock()->GetLayers() - 1;
	if (m_CurrentPos.y == layers)
	{
		Kill();
		return;
	}
	int randomDirection = rand()%2;
	IPoint2 movement{ 0,0 };
	randomDirection == 0 ? movement = { 0,1 } : movement = { 1,1 };

	m_CurrentPos.x += movement.x;
	m_CurrentPos.y += movement.y;

	if (m_CurrentPos.x < 0)
		m_CurrentPos.x = 0;
	if (m_CurrentPos.x > layers)
		m_CurrentPos.x = layers;

	auto gridBlock = tempGrid.lock()->GetGridFromPyramidIndex(m_CurrentPos.x, m_CurrentPos.y);

	glm::vec3 newPos = gridBlock.lock()->GetTransform().GetPosition();
	m_pParent.lock()->SetPosition(newPos.x, newPos.y - tempGrid.lock()->GetGridOffsets().y);
	tempGrid.lock()->NotifyGridblockToggle({ m_CurrentPos.x,m_CurrentPos.y }, 0, -1);

	auto Audio = ServiceLocator::getAudio();
	Audio->Play("Enemy_Jump", 1);

	m_moveCooldown = m_maxMoveCooldown;

}