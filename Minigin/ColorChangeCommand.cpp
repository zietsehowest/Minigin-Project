#include "MiniginPCH.h"
#include "ColorChangeCommand.h"
#include "GameObject.h"
#include "StatsComponent.h"
void dae::ColorChangeCommand::AddScore()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<StatsComponent>().expired())
	{
		m_Target.lock()->GetComponent<StatsComponent>().lock()->ChangeScore(25);
	}
}
                     