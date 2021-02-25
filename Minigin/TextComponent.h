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

		void SetText(const std::string& text, const std::shared_ptr<Font>& font,const SDL_Color color);

		inline void SetNeedsUpdate() { m_NeedsUpdate = true; }
		TextComponent(std::shared_ptr<GameObject> parent);
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

