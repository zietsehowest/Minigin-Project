#include "MiniginPCH.h"
#include "KillCommand.h"
#include "GameObject.h"
#include "StatsComponent.h"
void GameEngine::Killcommand::Kill()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<StatsComponent>().expired())
	{
		m_Target.lock()->GetComponent<StatsComponent>().lock()->Attack();
	}
}
