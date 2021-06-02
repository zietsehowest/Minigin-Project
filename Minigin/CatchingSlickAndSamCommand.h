#pragma once
#include "Command.h"
namespace GameEngine
{
	class GameObject;
	class CatchingSlickAndSamCommand final : public Command
	{
	public:
		CatchingSlickAndSamCommand(std::weak_ptr<GameObject> target)
			:m_Target{ target }
		{
		}
		virtual void Execute() { AddScore(); }
	private:
		void AddScore();
		std::weak_ptr<GameObject> m_Target;
	};
}

