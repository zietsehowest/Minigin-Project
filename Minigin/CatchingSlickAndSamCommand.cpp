#include "MiniginPCH.h"
#include "CatchingSlickAndSamCommand.h"
#include "GameObject.h"
#include "StatsComponent.h"
void dae::CatchingSlickAndSamCommand::AddScore()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<StatsComponent>().expired())
	{
		m_Target.lock()->GetComponent<StatsComponent>().lock()->ChangeScore(300);
	}
}