#pragma once
#include "Transform.h"
#include <SDL.h>
#include <SDL_ttf.h>
namespace GameEngine
{
	class Font;
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void Update(float) = 0;
		virtual void Render(const Transform& transform) const = 0;

		BaseComponent(std::shared_ptr<GameObject> parent);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	protected:
		std::weak_ptr<GameObject> m_pParent;
	};
}

