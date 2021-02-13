#pragma once
#include "Transform.h"
namespace dae
{

	class BaseComponent
	{
	public:
		virtual void Update(float) = 0;
		virtual void Render(const Transform& transform) const = 0;

		virtual void SetTexture(const std::string& filename) = 0;

		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	};
}

