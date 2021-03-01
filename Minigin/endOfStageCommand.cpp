#include "MiniginPCH.h"
#include "endOfStageCommand.h"
#include "GameObject.h"
#include "StatsComponent.h"
void dae::endOfStageCommand::AddScore()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<StatsComponent>().expired())
	{
		m_Target.lock()->GetComponent<StatsComponent>().lock()->ChangeScore(50);
	}
}