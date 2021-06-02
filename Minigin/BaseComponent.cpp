#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
GameEngine::BaseComponent::BaseComponent(std::shared_ptr<GameObject> parent)
	:m_pParent{ parent }
{
}
