#pragma once
#include "TextComponent.h"
#include "BaseComponent.h"
namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		virtual void Update(float) override;
		virtual void Render(const Transform& Transform) const override;

		virtual void SetText(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color color) override;
		virtual void SetTexture(const std::string&) override {};
		
		FPSComponent() = default;
		virtual ~FPSComponent();
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		std::shared_ptr<TextComponent> m_TextComponent = std::make_shared<TextComponent>();
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<SDL_Color> m_pColor;
		int m_Fps;
		int m_OldFps;
		void UpdateText();
	};
}

