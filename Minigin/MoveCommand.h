#pragma once
#include "Command.h"
namespace GameEngine
{
	enum class MoveDirection {
		topleft,
		topright,
		bottomleft, 
		bottomright
	};
	class GameObject;
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(std::weak_ptr<GameObject> target, const MoveDirection& direction)
			:m_Target{ target }
			,m_CommandDirection{direction}
		{
		}
		virtual void Execute() { MovePlayer(); }
	private:
		void MovePlayer();
		MoveDirection m_CommandDirection;
		std::weak_ptr<GameObject> m_Target;
	};
}

