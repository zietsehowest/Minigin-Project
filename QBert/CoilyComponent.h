#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "utils.h"
namespace GameEngine
{ 
	enum class CoilyState { traverse, chase };
	class GameObject;
	class CoilyComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		void Kill();

		void Move();

		CoilyComponent(std::shared_ptr<GameObject> parent,std::shared_ptr<GameObject> target, std::weak_ptr<GameObject> grid,const std::string& evolutionTexture);
		virtual ~CoilyComponent();
		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) = delete;

	private:
		CoilyState m_CoilyState;
		IPoint2 m_CurrentPos;
		std::weak_ptr<GameObject> m_pGrid;
		std::weak_ptr<GameObject> m_pTarget;
		float m_moveCooldown;
		float m_maxMoveCooldown;
		std::string m_EvolutionTexture;
	};
}


