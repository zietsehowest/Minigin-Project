#include "MiniginPCH.h"
#include "MoveCommand.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "../QBert/CoilyComponent.h"
using namespace GameEngine;
void MoveCommand::MovePlayer()
{
	if (!m_Target.expired() && (!m_Target.lock()->GetComponent<PlayerComponent>().expired() || !m_Target.lock()->GetComponent<CoilyComponent>().expired()))
	{
		IPoint2 temp{};
		switch (m_CommandDirection)
		{
		case MoveDirection::topleft:
			temp = { -1,-1 };
			break;
		case MoveDirection::topright:
			temp = { 0,-1 };
			break;
		case MoveDirection::bottomleft:
			temp = { 0,1 };
			break;
		case MoveDirection::bottomright:
			temp = { 1,1 };
			break;
		}
		if (m_IsPlayer)
			m_Target.lock()->GetComponent<PlayerComponent>().lock()->Move(temp);
		else if(!m_IsPlayer)
			m_Target.lock()->GetComponent<CoilyComponent>().lock()->Move(true, temp);
	}
}