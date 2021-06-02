#pragma once
#include "BaseComponent.h"
namespace GameEngine
{
	class GameObject;
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		virtual void Update(float) override;
		virtual void Render(const Transform& transform) const override;

		void SetTexture(const std::string& filename);

		RenderComponent(std::shared_ptr<GameObject> parent);
		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}

