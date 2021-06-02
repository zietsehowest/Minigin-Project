#include "MiniginPCH.h"
#include "flyingDiscCoilyCommand.h"
#include "GameObject.h"
#include "StatsComponent.h"
void GameEngine::flyingDiscCoilyCommand::AddScore()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<StatsComponent>().expired())
	{
		m_Target.lock()->GetComponent<StatsComponent>().lock()->ChangeScore(500);
	}
}
