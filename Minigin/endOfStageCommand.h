#pragma once
#include "Command.h"
namespace GameEngine
{
	class GameObject;
	class endOfStageCommand final : public Command
	{
	public:
		endOfStageCommand(std::weak_ptr<GameObject> target)
			:m_Target{ target }
		{
		}
		virtual void Execute() { AddScore(); }
	private:
		void AddScore();
		std::weak_ptr<GameObject> m_Target;
	};
}

