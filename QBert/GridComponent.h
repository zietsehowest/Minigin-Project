#pragma once
#include <MiniginPCH.h>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include <map>
#include "ManagerComponent.h"
namespace GameEngine
{
	class GridComponent : public BaseComponent
	{
	public:

		virtual void Update(float) override;
		virtual void Render(const Transform&) const {};

		GridComponent(std::shared_ptr<GameObject> parent,const std::string& gridFilePath,Gamemode mode,GameLevel level = GameLevel::lvl1);
		virtual ~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

		std::weak_ptr<GameObject> GetGridFromPyramidIndex(int x, int y);

		FVector2 GetGridOffsets() const { return m_offsets; }
		FVector2 GetStartPos() const { return m_StartPos; }
		int GetLayers() const { return m_Layers; }
		Gamemode GetGameMode() const { return m_Gamemode; }
		GameLevel GetGameLevel() const { return m_Level; }

		void SetGameLevel(GameLevel level) { m_Level = level; }

		bool NotifyGridblockToggle(IPoint2 pos, int gameMode,int deactivateOrActivate);

		std::weak_ptr<GameObject> checkForDisk(int lineHeight, int leftOrRight);

		bool HasClearedLevel();
	private:
		void ReadGridData(const std::string& gridPath);
		void MakeGrid();
		void FillVector();

		Gamemode m_Gamemode;
		GameLevel m_Level;

		float m_BlockWidth;
		float m_BlockHeight;
		FVector2 m_offsets;
		std::vector<std::string> m_Blockpaths;
		FVector2 m_StartPos;
		int m_Layers;
		std::vector<std::vector<std::shared_ptr<GameObject>>> m_pGridBlocks;
		std::vector<std::shared_ptr<GameObject>> m_pDisks;
		std::vector<std::shared_ptr<Texture2D>> m_pBlockTextures;

		void clearGrid();

		void generateRows(int rowCount, float startX);
	};
}


