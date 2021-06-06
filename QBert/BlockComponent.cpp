#include "BlockComponent.h"
using namespace GameEngine;
BlockComponent::BlockComponent(std::shared_ptr<GameObject> parent) : BaseComponent(parent)
	,m_CurrentState{BlockState::state1}
{

}
void BlockComponent::ToggleBlock(int level)
{
	if (level == 0)
		m_CurrentState = BlockState::state2;
	if (level == 1)
	{
		if (m_CurrentState == BlockState::state1)
			m_CurrentState = BlockState::state3;
		else if (m_CurrentState == BlockState::state3)
			m_CurrentState = BlockState::state2;
	}
	if (level == 2)
	{
		if (m_CurrentState == BlockState::state1)
			m_CurrentState = BlockState::state2;
		else
			m_CurrentState = BlockState::state1;
	}

}
void BlockComponent::DownGradeBlock()
{
	if (m_CurrentState == BlockState::state1)
		return;
	else
		m_CurrentState = BlockState((int)m_CurrentState - 1);
}
void BlockComponent::Update(float)
{
}
BlockComponent::~BlockComponent()
{
}
