#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		virtual void Update(float) override;
		virtual void Render(const Transform& transform) const override;

		virtual void SetText(const std::string& text, const std::shared_ptr<Font>& font,const SDL_Color color) override;

		virtual void SetTexture(const std::string& filename) override;

		TextComponent() = default;
		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<SDL_Color> m_pColor;
	};
}

