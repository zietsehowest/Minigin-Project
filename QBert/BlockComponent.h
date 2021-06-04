#pragma once
#include <MiniginPCH.h>
#include <BaseComponent.h>
#include <GameObject.h>
#include <Texture2D.h>
namespace GameEngine
{
	enum class BlockState
	{
		state1=0,
		state2=1,
		state3=2
	};
	class BlockComponent : public BaseComponent
	{
	public:
		virtual void Update(float) override;
		virtual void Render(const Transform&) const {};

		BlockState GetBlockState() const { return m_CurrentState; }
		void UpgradeBlock(int gamemode);
		void DownGradeBlock();

		BlockComponent(std::shared_ptr<GameObject> parent);
		virtual ~BlockComponent();
		BlockComponent(const BlockComponent& other) = delete;
		BlockComponent(BlockComponent&& other) = delete;
		BlockComponent& operator=(const BlockComponent& other) = delete;
		BlockComponent& operator=(BlockComponent&& other) = delete;
	private:
		BlockState m_CurrentState;
	};
}

