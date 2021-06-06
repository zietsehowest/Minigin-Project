#include "GridComponent.h"
#include "ResourceManager.h"
#include <fstream>
#include <regex>
#include "GameObject.h"
#include "SceneManager.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "BlockComponent.h"
#include "DiskComponent.h"
using namespace GameEngine;
GridComponent::GridComponent(std::shared_ptr<GameObject> parent, const std::string& gridFilePath,Gamemode mode,GameLevel level) : BaseComponent(parent)
	,m_Gamemode{mode}
	,m_Level{level}
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

	//check if we have a disk on this layer
	auto leftFromRow = checkForDisk(0, -1);
	auto rightFromRow = checkForDisk(0, 1);
	if (!leftFromRow.expired()) //disk on the left
	{
		leftFromRow.lock()->SetPosition(m_StartPos.x - m_BlockWidth / 2, m_StartPos.y - m_BlockHeight);
	}
	if (!rightFromRow.expired()) //disk on the right
	{
		rightFromRow.lock()->SetPosition(m_StartPos.x + m_BlockWidth /2, m_StartPos.y - m_BlockHeight);
	}

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

	//check if we have a disk on this layer
	auto leftFromRow = checkForDisk(rowCount, -1);
	auto rightFromRow = checkForDisk(rowCount, 1);

	if (!leftFromRow.expired()) //disk on the left
	{
		leftFromRow.lock()->SetPosition(startX - m_BlockWidth / 2, Height - m_BlockHeight);
	}
	if (!rightFromRow.expired()) //disk on the right
	{
		rightFromRow.lock()->SetPosition(endX + m_BlockWidth / 2, Height - m_BlockHeight);
	}


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
bool GridComponent::NotifyGridblockToggle(IPoint2 pos, int gameMode, int deactivateOrActivate)
{
	auto go = GetGridFromPyramidIndex(pos.x, pos.y);
	auto tempBlock = go.lock()->GetComponent<BlockComponent>().lock();
	
	BlockState previousState = tempBlock->GetBlockState();
	
	deactivateOrActivate == 1 ? tempBlock->ToggleBlock(gameMode) : tempBlock->DownGradeBlock(); //check if we want to downgrade or toggle a block (downgrading for slick&sam)
	
	auto blockState = go.lock()->GetComponent<BlockComponent>().lock()->GetBlockState();

	if (previousState == blockState)
		return false;
	go.lock()->GetComponent<RenderComponent>().lock()->SetTexture(m_pBlockTextures[(int)blockState]);
	
	if (gameMode == (int)GameLevel::lvl3)
		return false;

	return true;
}
std::weak_ptr<GameObject> GridComponent::GetGridFromPyramidIndex(int x, int y)
{
	return m_pGridBlocks[x][y];
}
std::weak_ptr<GameObject> GridComponent::checkForDisk(int lineHeight, int leftOrRight)
{
		auto it = std::find_if(m_pDisks.begin(), m_pDisks.end(), [lineHeight, leftOrRight](std::shared_ptr<GameObject> ob)
		{
			auto coordinates = ob.get()->GetComponent<DiskComponent>().lock()->GetDiskCoordinates();
			return (coordinates.x == lineHeight && coordinates.y == leftOrRight);
		});
		if (it != m_pDisks.end()) //we have a disk here
		{
			return *it;
		}
		else
			return std::shared_ptr<GameObject>(nullptr);
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
				if (match[1] == "tb")
					m_Blockpaths.push_back(match[2]);
				if (match[1] == "bl")
					m_Layers = std::stoi(match[2]);
				if (match[1] == "x")//x start position
					m_StartPos.x = std::stof(match[2]);
				if (match[1] == "y")//y start position
					m_StartPos.y = std::stof(match[2]);
				if (match[1] == "ev") //found elevator
				{
					std::regex tempRegex{ "(\\d+),(-?\\d)$" };
					std::string tempLine = match[2];
					std::smatch tempMatch;
					if (std::regex_match(tempLine, tempMatch, tempRegex))
					{
						auto go = std::make_shared<GameObject>();
						go->AddComponent(std::make_shared<DiskComponent>(go,IPoint2{std::stoi(tempMatch[1]),std::stoi(tempMatch[2])}));
						go->AddComponent(std::make_shared<RenderComponent>(go));
						go->GetComponent<RenderComponent>().lock()->SetTexture("../Data/Disk.png");
						SceneManager::GetInstance().GetCurrentScene().lock()->Add(go);
						m_pDisks.push_back(go);
					}
				}

			}
		}
	}
	else
		std::cerr << "Grid File couldn't be opened";

}


