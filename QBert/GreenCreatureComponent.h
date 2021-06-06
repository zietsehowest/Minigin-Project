#pragma once
#include "MiniginPCH.h"
#include <BaseComponent.h>
#include "utils.h"
namespace GameEngine
{
	class GreenCreatureComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		void Kill();

		void Move();

		IPoint2 GetCurrentGridPos() { return m_CurrentPos; }

		GreenCreatureComponent(std::shared_ptr<GameObject> parent, std::weak_ptr<GameObject> grid, const std::vector<std::string>& texturePaths);
		virtual ~GreenCreatureComponent();
		GreenCreatureComponent(const GreenCreatureComponent& other) = delete;
		GreenCreatureComponent(GreenCreatureComponent&& other) = delete;
		GreenCreatureComponent& operator=(const GreenCreatureComponent& other) = delete;
		GreenCreatureComponent& operator=(GreenCreatureComponent&& other) = delete;
	private:
		IPoint2 m_CurrentPos;
		std::weak_ptr<GameObject> m_pGrid;
		float m_moveCooldown;
		float m_maxMoveCooldown;
	};
}

