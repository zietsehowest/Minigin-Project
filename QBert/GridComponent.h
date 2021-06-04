#pragma once
#include <MiniginPCH.h>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
namespace GameEngine
{
	class GridComponent : public BaseComponent
	{
	public:

		virtual void Update(float) override;
		virtual void Render(const Transform&) const {};

		GridComponent(std::shared_ptr<GameObject> parent,const std::string& gridFilePath);
		virtual ~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;

		std::weak_ptr<GameObject> GetGridFromPyramidIndex(int x, int y);
	private:
		void ReadGridData(const std::string& gridPath);
		void MakeGrid();
		void FillVector();

		float m_BlockWidth;
		float m_BlockHeight;
		std::vector<std::string> m_Blockpaths;
		FVector2 m_StartPos;
		int m_Layers;
		std::vector<std::vector<std::shared_ptr<GameObject>>> m_pGridBlocks;
		std::vector<std::shared_ptr<Texture2D>> m_pBlockTextures;

		void generateRows(int rowCount, float startX);
	};
}


