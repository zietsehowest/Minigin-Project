#include "MiniginPCH.h"

#include "TextComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
dae::TextComponent::~TextComponent() {};
void dae::TextComponent::SetTexture(const std::string&) {};
void dae::TextComponent::Update(float elapsedSec)
{
	if (m_NeedsUpdate && elapsedSec != 0.f) //need to fix this elapsedSec later !
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), *m_pColor);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render(const Transform& transform) const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text, const std::shared_ptr<Font>& font,const SDL_Color color)
{
	m_Text = text;
	m_NeedsUpdate = true;
	m_pFont = font;
	m_pColor = std::make_shared<SDL_Color>(color);
}
