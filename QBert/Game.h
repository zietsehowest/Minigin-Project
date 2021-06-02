#pragma once
#include <Core.h>
namespace GameEngine
{
	class Game final : public GameEngine::Core
	{
	public:
		virtual void LoadGame() const override;
	private:
	};
}

