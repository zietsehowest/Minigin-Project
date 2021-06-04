#pragma once
#include "MiniginPCH.h"
#include <BaseComponent.h>
#include "utils.h"
namespace GameEngine
{
	enum class EnemyType{wrongway,ugg};
	class GameObject;
	class PurpleCreatureComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		void Kill();

		void Move();

		PurpleCreatureComponent(std::shared_ptr<GameObject> parent,std::weak_ptr<GameObject> grid,const EnemyType& type,const std::vector<std::string>& texturePaths);
		virtual ~PurpleCreatureComponent();
		PurpleCreatureComponent(const PurpleCreatureComponent& other) = delete;
		PurpleCreatureComponent(PurpleCreatureComponent&& other) = delete;
		PurpleCreatureComponent& operator=(const PurpleCreatureComponent& other) = delete;
		PurpleCreatureComponent& operator=(PurpleCreatureComponent&& other) = delete;
	private:
		EnemyType m_Type;
		IPoint2 m_CurrentPos;
		std::weak_ptr<GameObject> m_pGrid;
		float m_moveCooldown;
		float m_maxMoveCooldown;
		float m_HeightOffset;
	};
}


