#pragma once
#include <MiniginPCH.h>
#include <BaseComponent.h>
#include <GameObject.h>
namespace GameEngine
{
	class FinalScreenComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const;

		void SetText(const std::string& text) { m_FinalString = text; };

		FinalScreenComponent(std::shared_ptr<GameObject> parent,std::string finalScreenText);
		virtual ~FinalScreenComponent() = default;
		FinalScreenComponent(const FinalScreenComponent& other) = delete;
		FinalScreenComponent(FinalScreenComponent&& other) = delete;
		FinalScreenComponent& operator=(const FinalScreenComponent& other) = delete;
		FinalScreenComponent& operator=(FinalScreenComponent&& other) = delete;
	private:
		std::string m_FinalString;
	};
}

