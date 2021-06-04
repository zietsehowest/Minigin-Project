#include "GridComponent.h"
#include "ResourceManager.h"
#include <fstream>
#include <regex>
#include "GameObject.h"
#include "SceneManager.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "BlockComponent.h"
using namespace GameEngine;
GridComponent::GridComponent(std::shared_ptr<GameObject> parent, const std::string& gridFilePath) : BaseComponent(parent)
{

	ReadGridData(gridFilePath);

	FillVector();

	if (m_Blockpaths.size() == 2)
	{
		m_pBlockTextures.push_back(ResourceManager::GetInstance().LoadTexture(m_Blockpaths[0]));
		m_pBlockTextures.push_back(ResourceManager::GetInstance().LoadTexture(m_Blockpaths[1]));
	}
	if (m_Blockpaths.size() == 3)
	{
		m_pBlockTextures.push_back(ResourceManager::GetInstance().LoadTexture(m_Blockpaths[0]));
		m_pBlockTextures.push_back(ResourceManager::GetInstance().LoadTexture(m_Blockpaths[1]));
		m_pBlockTextures.push_back(ResourceManager::GetInstance().LoadTexture(m_Blockpaths[2]));
	}

	MakeGrid();

	m_offsets.x = m_BlockWidth / 2;
	m_offsets.y = m_BlockHeight / 2;
}
void GridComponent::MakeGrid()
{
	auto gridBlock = std::make_shared<GameObject>();
	gridBlock->AddComponent(std::make_shared<RenderComponent>(gridBlock));
	gridBlock->AddComponent(std::make_shared<BlockComponent>(gridBlock));
	gridBlock->GetComponent<RenderComponent>().lock()->SetTexture(m_pBlockTextures[0]);
	gridBlock->SetPosition(m_StartPos.x, m_StartPos.y);
	m_pGridBlocks[0][0] = gridBlock;
	SceneManager::GetInstance().GetCurrentScene().lock()->Add(gridBlock);

	generateRows(1, m_StartPos.x - m_BlockWidth / 2);

}
void GridComponent::FillVector()
{
	for (int i = 0; i < m_Layers; i++)
	{
		std::vector<std::shared_ptr<GameObject>> temp;
		for (int j = 0; j < m_Layers; j++)
			temp.push_back(nullptr);

		m_pGridBlocks.push_back(temp);
	}
}
void GridComponent::generateRows(int rowCount,float startX)
{
	if (rowCount == m_Layers)
		return;
	float Height = m_StartPos.y + rowCount * m_BlockHeight;
	float endX = startX + rowCount * m_BlockWidth;
	int counter = 0;
	for (float i = startX; i <= endX; i += m_BlockWidth)
	{
		auto gridBlock = std::make_shared<GameObject>();
		gridBlock->AddComponent(std::make_shared<RenderComponent>(gridBlock));
		gridBlock->AddComponent(std::make_shared<BlockComponent>(gridBlock));
		gridBlock->GetComponent<RenderComponent>().lock()->SetTexture(m_pBlockTextures[0]);
		gridBlock->SetPosition(i, Height);
		m_pGridBlocks[counter][rowCount] = (gridBlock);
		SceneManager::GetInstance().GetCurrentScene().lock()->Add(gridBlock);
		counter++;
	}
	generateRows(++rowCount, startX - m_BlockWidth/2);

	
}
void GridComponent::Update(float)
{
	
}
void GridComponent::NotifyGridblockToggle(IPoint2 pos, int gameMode, int deactivateOrActivate)
{
	auto go = GetGridFromPyramidIndex(pos.x, pos.y);
	auto tempBlock = go.lock()->GetComponent<BlockComponent>().lock();
	deactivateOrActivate == 1 ? tempBlock->UpgradeBlock(gameMode) : tempBlock->DownGradeBlock();
	auto blockState = go.lock()->GetComponent<BlockComponent>().lock()->GetBlockState();
	go.lock()->GetComponent<RenderComponent>().lock()->SetTexture(m_pBlockTextures[(int)blockState]);
}
std::weak_ptr<GameObject> GridComponent::GetGridFromPyramidIndex(int x, int y)
{
	return m_pGridBlocks[x][y];
}
void GridComponent::ReadGridData(const std::string& gridPath)
{
	std::ifstream is;
	std::regex regex{ "(.{1,}):(.{1,})" };
	std::string line;
	std::smatch match;
	is.open(gridPath);
	if (is.is_open())
	{
		while (std::getline(is, line))
		{
			if (std::regex_match(line, match, regex))
			{
				if (match[1] == "bw")
					m_BlockWidth = std::stof(match[2]);
				if (match[1] == "bh")
					m_BlockHeight = std::stof(match[2]);
				if (match[1] == "pb")
					m_Blockpaths.push_back(match[2]);
				if (match[1] == "sb")
					m_Blockpaths.push_back(match[2]);
				if (match[1] == "bl")
					m_Layers = std::stoi(match[2]);
				if (match[1] == "x")
					m_StartPos.x = std::stof(match[2]);
				if (match[1] == "y")
					m_StartPos.y = std::stof(match[2]);
			}
		}
	}
	else
		std::cerr << "Grid File couldn't be opened";

}


