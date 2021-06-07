#pragma once
#include <MiniginPCH.h>
#include <BaseComponent.h>
#include <GameObject.h>
namespace GameEngine
{
	class StartScreenComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const;

		StartScreenComponent(std::shared_ptr<GameObject> parent);
		virtual ~StartScreenComponent() = default;
		StartScreenComponent(const StartScreenComponent& other) = delete;
		StartScreenComponent(StartScreenComponent&& other) = delete;
		StartScreenComponent& operator=(const StartScreenComponent& other) = delete;
		StartScreenComponent& operator=(StartScreenComponent&& other) = delete;
	private:

	};
}


