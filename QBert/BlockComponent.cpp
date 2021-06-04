#include "BlockComponent.h"
using namespace GameEngine;
BlockComponent::BlockComponent(std::shared_ptr<GameObject> parent) : BaseComponent(parent)
	,m_CurrentState{BlockState::state1}
{

}
void BlockComponent::UpgradeBlock(int gamemode)
{
	if (gamemode == 0)
		m_CurrentState = BlockState::state2;
	if (gamemode == 1)
	{
		if (m_CurrentState == BlockState::state1)
			m_CurrentState = BlockState::state3;
		else if (m_CurrentState == BlockState::state3)
			m_CurrentState = BlockState::state2;
	}

}
void BlockComponent::DownGradeBlock()
{
	if (m_CurrentState == BlockState::state2)
		m_CurrentState = BlockState::state1;
}
void BlockComponent::Update(float)
{
}
BlockComponent::~BlockComponent()
{
}
