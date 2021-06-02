#pragma once
#include <memory>
#include "BaseComponent.h"
namespace GameEngine
{
	class StatsComponent : public BaseComponent
	{
	public:
		StatsComponent(std::shared_ptr<GameObject>& parent,int startLives);
		virtual ~StatsComponent() = default;
		StatsComponent(const StatsComponent& other) = delete;
		StatsComponent(StatsComponent&& other) = delete;
		StatsComponent& operator=(const StatsComponent& other) = delete;
		StatsComponent& operator=(StatsComponent&& other) = delete;

		void Attack();

		void ChangeScore(int points);

		inline int GetLives() const { return m_Lives; }

		inline int GetScore() const { return m_Score; }
		
		virtual void Update(float) override {};
		virtual void Render(const Transform&) const override {};
	
	private:
		int m_Lives;
		int m_Score;
	};
}

