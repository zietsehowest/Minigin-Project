#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include <memory>
#include "GameObject.h"
#include "StatsComponent.h"
#include <string>
namespace dae
{
	class CharacterObserver : public Observer
	{
	public:
		CharacterObserver(std::weak_ptr<TextComponent> healthText,std::weak_ptr<TextComponent> scoreText)
			:m_pHealthText{healthText}
			,m_pScoreText{scoreText}
		{

		}
		virtual void onNotify(std::weak_ptr<GameObject>& character, EventType eventType) override
		{
			switch (eventType)
			{
			case EVENT_PLAYER_DEATH:
				if (character.lock()->GetComponent<StatsComponent>().lock() != nullptr)
				{
					int lives = character.lock()->GetComponent<StatsComponent>().lock()->GetLives();
					std::string text = "Lives: ";
					text += std::to_string(lives);
					m_pHealthText.lock()->SetText(text,m_pHealthText.lock()->GetFont(),*m_pHealthText.lock()->GetColor());
				}
				break;
			case EVENT_PLAYER_SCORE_CHANGED:
				if (character.lock()->GetComponent<StatsComponent>().lock() != nullptr)
				{
					int score = character.lock()->GetComponent<StatsComponent>().lock()->GetScore();
					m_pScoreText.lock()->SetText("Score: " + std::to_string(score), m_pScoreText.lock()->GetFont(), *m_pScoreText.lock()->GetColor());
				}
				break;
			}
		}
	private:
		std::weak_ptr<TextComponent> m_pHealthText;
		std::weak_ptr<TextComponent> m_pScoreText;
	};
}

