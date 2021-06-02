#include "MiniginPCH.h"
#include "SubjectComponent.h"
GameEngine::SubjectComponent::SubjectComponent(std::shared_ptr<GameObject>& parent) : BaseComponent(parent)
{
}
void GameEngine::SubjectComponent::AddObserver(const std::shared_ptr<Observer>& observerToAdd)
{
	m_pObservers.push_back(observerToAdd);
}
void GameEngine::SubjectComponent::RemoveObserver(const std::shared_ptr<Observer>&)
{
	//TODO
}
void GameEngine::SubjectComponent::Notify(std::weak_ptr<GameObject>& entity, EventType eventType)
{
	for (auto observer : m_pObservers)
	{
		observer->onNotify(entity, eventType);
	}
}
