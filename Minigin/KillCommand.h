#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class Killcommand final : public Command
	{
	public:
		Killcommand(std::weak_ptr<GameObject> target) 
			:m_Target{ target }
		{
		}
		virtual void Execute() { Kill(); }
	private:
		void Kill();
		std::weak_ptr<GameObject> m_Target;
	};

}

