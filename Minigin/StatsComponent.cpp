#include "MiniginPCH.h"
#include "StatsComponent.h"
#include "GameObject.h"
#include "SubjectComponent.h"
GameEngine::StatsComponent::StatsComponent(std::shared_ptr<GameObject>& parent,int startLives) : BaseComponent(parent)
	,m_Lives{startLives}
	,m_Score{0}
{
}
void GameEngine::StatsComponent::Attack()
{
	m_Lives--;
	if (m_pParent.lock()->GetComponent<SubjectComponent>().lock())
		m_pParent.lock()->GetComponent<SubjectComponent>().lock()->Notify(m_pParent, EVENT_PLAYER_DEATH);
	if (m_Lives <= 0)
	{
		//bring game back to main menu or close game
	}
}
void GameEngine::StatsComponent::ChangeScore(int points)
{
	m_Score += points;
	if (m_pParent.lock()->GetComponent<SubjectComponent>().lock())
		m_pParent.lock()->GetComponent<SubjectComponent>().lock()->Notify(m_pParent, EVENT_PLAYER_SCORE_CHANGED);
}
