#pragma once
#include "BaseComponent.h"
#include "utils.h"
namespace GameEngine
{
	class GameObject;
	class PlayerComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		void Kill();

		void Move(const IPoint2& moveDirection);

		IPoint2 GetCurrentGridPos() const { return m_CurrentPos; }

		void ResetPosition();

		PlayerComponent(std::shared_ptr<GameObject> parent,std::weak_ptr<GameObject> grid);
		virtual ~PlayerComponent();
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
	
	private:
		IPoint2 m_CurrentPos;
		std::weak_ptr<GameObject> m_pGrid;
		float m_moveCooldown;
		float m_maxMoveCooldown;
	};
}

