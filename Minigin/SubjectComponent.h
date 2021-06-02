#pragma once
#include <memory>
#include <vector>
#include "BaseComponent.h"
#include "Observer.h"
namespace GameEngine
{
	class SubjectComponent : public BaseComponent
	{
	public:
		SubjectComponent(std::shared_ptr<GameObject>& parent);
		virtual ~SubjectComponent() = default;
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;

		virtual void Update(float) override {};
		virtual void Render(const Transform&) const override {};
		
		//Functions
		void AddObserver(const std::shared_ptr<Observer>& observerToAdd);
		void RemoveObserver(const std::shared_ptr<Observer>& observerToRemove);
		void Notify(std::weak_ptr<GameObject>& entity, EventType eventType);
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}

