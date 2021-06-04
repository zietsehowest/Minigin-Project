#include "MiniginPCH.h"
#include "MoveCommand.h"
#include "GameObject.h"
#include "PlayerComponent.h"
using namespace GameEngine;
void MoveCommand::MovePlayer()
{
	if (!m_Target.expired() && !m_Target.lock()->GetComponent<PlayerComponent>().expired())
	{
		IPoint2 temp;
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
		m_Target.lock()->GetComponent<PlayerComponent>().lock()->Move(temp);
	}
}