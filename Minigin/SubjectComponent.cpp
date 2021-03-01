#include "MiniginPCH.h"
#include "SubjectComponent.h"
dae::SubjectComponent::SubjectComponent(std::shared_ptr<GameObject>& parent) : BaseComponent(parent)
{
}
void dae::SubjectComponent::AddObserver(const std::shared_ptr<Observer>& observerToAdd)
{
	m_pObservers.push_back(observerToAdd);
}
void dae::SubjectComponent::RemoveObserver(const std::shared_ptr<Observer>&)
{
	//TODO
}
void dae::SubjectComponent::Notify(std::weak_ptr<GameObject>& entity, EventType eventType)
{
	for (auto observer : m_pObservers)
	{
		observer->onNotify(entity, eventType);
	}
}
