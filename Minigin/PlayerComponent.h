#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PlayerComponent : public BaseComponent
	{
	public:
		virtual void Update(float) override;
		virtual void Render(const Transform&) {};

		void Kill();

		PlayerComponent(std::shared_ptr<GameObject> parent,int lives = 0);
		virtual ~PlayerComponent();
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
	
	private:
		int m_Lives;
	};
}

