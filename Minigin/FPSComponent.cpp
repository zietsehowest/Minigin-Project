#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <chrono>
#include <string>
GameEngine::FPSComponent::FPSComponent(std::shared_ptr<GameObject>& parent) : BaseComponent(parent)
{
	m_TextComponent = std::make_shared<TextComponent>(parent);
}
GameEngine::FPSComponent::~FPSComponent() {};
void GameEngine::FPSComponent::Update(float elapsedSec)
{
	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int tempFps; tempFps++;
	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 } && tempFps != m_Fps) 
	{
		oldTime = std::chrono::high_resolution_clock::now();
		m_Fps = tempFps;
		UpdateText(); //updating the text object before updating and rendering the full texture again in the textComponents
		tempFps = 0;
		m_TextComponent->SetNeedsUpdate();
	}
	if (m_TextComponent != nullptr)
	{
		m_TextComponent->Update(elapsedSec);
	}
}
void GameEngine::FPSComponent::Render(const Transform& transform) const
{
	if (m_TextComponent != nullptr)
	{
		const auto pos = transform.GetPosition();
		m_TextComponent->Render(transform);
	}
}
void GameEngine::FPSComponent::SetText(const std::string&, const std::shared_ptr<Font>& font, const SDL_Color color)
{
	m_TextComponent->SetText(std::to_string(m_Fps),font,color);
	m_pFont = font;
	m_pColor = std::make_shared<SDL_Color>(color);

}
void GameEngine::FPSComponent::UpdateText()
{
	m_TextComponent->SetText(std::to_string(m_Fps), m_pFont, *m_pColor);
}