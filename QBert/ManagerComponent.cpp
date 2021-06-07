#include "ManagerComponent.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "MiniginPCH.h"
#include "Core.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "CharacterObserver.h"
#include "Observer.h"

#pragma region AudioIncludes
#include "Audio.h"
#include "ServiceLocator.h"
#include "AudioLogger.h"
#include "GameAudio.h"
#pragma endregion

#pragma region ComponentIncludes
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "SubjectComponent.h"
#include "StatsComponent.h"
#include "GridComponent.h"
#include "PlayerComponent.h"
#include "CoilyComponent.h"
#include "PurpleCreatureComponent.h"
#include "GreenCreatureComponent.h"
#pragma endregion

#pragma region CommandIncludes
#include "KillCommand.h"
#include "flyingDiscCoilyCommand.h"
#include "CatchingSlickAndSamCommand.h"
#include "endOfStageCommand.h"
#include "ColorChangeCommand.h"
#include "MoveCommand.h"
#pragma endregion
using namespace GameEngine;
ManagerComponent::ManagerComponent(std::shared_ptr<GameObject> parent, Gamemode mode) : BaseComponent(parent)
	,m_CurrentGamemode{mode}
	,m_CurrentLevel{GameLevel::lvl1}
	,m_HasCompletedLevel{false}
{
	switch (mode)
	{
	case Gamemode::singleplayer:
		InitializeSinglePlayer();
		SpawnEnemy(EnemyType::Coily);
		break;
	case Gamemode::coop:
		InitializeCoop();
		SpawnEnemy(EnemyType::Coily);
		break;
	case Gamemode::versus:
		InitializeVersus();
		break;
	}

	SpawnEnemy(EnemyType::GreenEnemy);
		
}
void ManagerComponent::Update(float)
{
	if (m_HasCompletedLevel)
	{
		m_pGrid.lock()->GetComponent<GridComponent>().lock()->InitializeNewLevel("../Data/Grid/GridInfo_"+ std::to_string((int)m_CurrentLevel) + ".txt", m_CurrentGamemode, m_CurrentLevel);
		m_HasCompletedLevel = false;
	}

	RemoveInactiveEnemies();
	HandleEnemyCollisions();


	if (!m_pGrid.expired() && m_pGrid.lock()->GetComponent<GridComponent>().lock()->HasClearedLevel()) // go to next level
	{
		RemoveAllEnemies();

		auto Audio = ServiceLocator::getAudio();
		Audio->Play("Level_Complete", 1);
		//reset level
		m_CurrentLevel = GameLevel((int)m_CurrentLevel + 1);

		if ((int)m_CurrentLevel > 2) //we finished the game !! go to endscreen
		{

		}
	}
}
void ManagerComponent::InitializeSinglePlayer()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene().lock();
	
	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("background.jpg");
	scene->Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//lives display
	auto lives = std::make_shared<GameObject>();
	lives->AddComponent(std::make_shared<TextComponent>(lives));
	lives->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,140,0 });
	lives->SetPosition(20, 30);
	scene->Add(lives);

	//score display
	auto score = std::make_shared<GameObject>();
	score->AddComponent(std::make_shared<TextComponent>(score));
	score->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,140,0 });
	score->SetPosition(20, 50);
	scene->Add(score);

	//adding grid
	auto grid = std::make_shared<GameObject>();
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_" + std::to_string((int)m_CurrentLevel) + ".txt",m_CurrentGamemode,m_CurrentLevel));
	scene->Add(grid);
	m_pGrid = grid;

	//Creating the Q*Bert
	auto temp = std::make_shared<GameObject>();
	temp->AddComponent(std::make_shared<RenderComponent>(temp));
	temp->GetComponent<RenderComponent>().lock()->SetTexture("QBertMain.png");
	temp->AddComponent(std::make_shared<StatsComponent>(temp, 3));
	temp->AddComponent(std::make_shared<SubjectComponent>(temp));
	temp->AddComponent(std::make_shared<PlayerComponent>(temp, grid));
	temp->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives->GetComponent<TextComponent>(), score->GetComponent<TextComponent>()));
	scene->Add(temp);
	m_Players.push_back(temp);

	//Command Initialize
	InputManager::GetInstance().AddControlInput({ SDLK_q,InputType::released,true }, std::make_shared<MoveCommand>(temp, MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ SDLK_e,InputType::released,true }, std::make_shared<MoveCommand>(temp, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ SDLK_a,InputType::released,true }, std::make_shared<MoveCommand>(temp, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ SDLK_d,InputType::released,true }, std::make_shared<MoveCommand>(temp, MoveDirection::bottomright));
}
void ManagerComponent::InitializeCoop()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene().lock();

	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("background.jpg");
	scene->Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

#pragma region Player1Creation
	//lives display
	auto lives = std::make_shared<GameObject>();
	lives->AddComponent(std::make_shared<TextComponent>(lives));
	lives->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,140,0 });
	lives->SetPosition(20, 30);
	scene->Add(lives);

	//score display
	auto score = std::make_shared<GameObject>();
	score->AddComponent(std::make_shared<TextComponent>(score));
	score->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,140,0 });
	score->SetPosition(20, 50);
	scene->Add(score);

	//adding grid
	auto grid = std::make_shared<GameObject>();
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_" + std::to_string((int)m_CurrentLevel) + ".txt",m_CurrentGamemode,m_CurrentLevel));
	scene->Add(grid);

	//Creating the Q*Bert
	auto qbert = std::make_shared<GameObject>();
	qbert->AddComponent(std::make_shared<RenderComponent>(qbert));
	qbert->GetComponent<RenderComponent>().lock()->SetTexture("QBertMain.png");
	qbert->AddComponent(std::make_shared<StatsComponent>(qbert, 3));
	qbert->AddComponent(std::make_shared<SubjectComponent>(qbert));
	qbert->AddComponent(std::make_shared<PlayerComponent>(qbert, grid));
	qbert->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives->GetComponent<TextComponent>(), score->GetComponent<TextComponent>()));
	scene->Add(qbert);
	m_Players.push_back(qbert);

#pragma endregion 

#pragma region Player2Creation
	//lives2 display
	auto lives2 = std::make_shared<GameObject>();
	lives2->AddComponent(std::make_shared<TextComponent>(lives2));
	lives2->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 246,190,0 });
	lives2->SetPosition(20,80);
	scene->Add(lives2);

	//score2 display
	auto score2 = std::make_shared<GameObject>();
	score2->AddComponent(std::make_shared<TextComponent>(score2));
	score2->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 246,190,0 });
	score2->SetPosition(20, 100);
	scene->Add(score2);

	//Creating the Q*Bert2
	auto qbert2 = std::make_shared<GameObject>();
	qbert2->AddComponent(std::make_shared<RenderComponent>(qbert2));
	qbert2->GetComponent<RenderComponent>().lock()->SetTexture("QBertSecond.png");
	qbert2->AddComponent(std::make_shared<StatsComponent>(qbert2, 3));
	qbert2->AddComponent(std::make_shared<SubjectComponent>(qbert2));
	qbert2->AddComponent(std::make_shared<PlayerComponent>(qbert2, grid,1));
	qbert2->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives2->GetComponent<TextComponent>(), score2->GetComponent<TextComponent>()));
	scene->Add(qbert2);
	m_Players.push_back(qbert2);
	m_pGrid = grid;

#pragma endregion
	//Command Initialize
	InputManager::GetInstance().AddControlInput({ SDLK_q,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ SDLK_e,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ SDLK_a,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ SDLK_d,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::bottomright));

	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPLEFT,InputType::released,false }, std::make_shared<MoveCommand>(qbert2, MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPRIGHT,InputType::released,false }, std::make_shared<MoveCommand>(qbert2, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNLEFT,InputType::released,false }, std::make_shared<MoveCommand>(qbert2, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNRIGHT,InputType::released,false }, std::make_shared<MoveCommand>(qbert2, MoveDirection::bottomright));
}
void ManagerComponent::InitializeVersus()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene().lock();

	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("background.jpg");
	scene->Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

#pragma region InitializeQBert
	//lives display
	auto lives = std::make_shared<GameObject>();
	lives->AddComponent(std::make_shared<TextComponent>(lives));
	lives->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,140,0 });
	lives->SetPosition(20, 30);
	scene->Add(lives);

	//score display
	auto score = std::make_shared<GameObject>();
	score->AddComponent(std::make_shared<TextComponent>(score));
	score->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,140,0 });
	score->SetPosition(20, 50);
	scene->Add(score);

	//adding grid
	auto grid = std::make_shared<GameObject>();
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_" + std::to_string((int)m_CurrentLevel) + ".txt", m_CurrentGamemode, m_CurrentLevel));
	scene->Add(grid);

	m_pGrid = grid;

	//Creating the Q*Bert
	auto qbert = std::make_shared<GameObject>();
	qbert->AddComponent(std::make_shared<RenderComponent>(qbert));
	qbert->GetComponent<RenderComponent>().lock()->SetTexture("QBertMain.png");
	qbert->AddComponent(std::make_shared<StatsComponent>(qbert, 3));
	qbert->AddComponent(std::make_shared<SubjectComponent>(qbert));
	qbert->AddComponent(std::make_shared<PlayerComponent>(qbert, grid));
	qbert->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives->GetComponent<TextComponent>(), score->GetComponent<TextComponent>()));
	scene->Add(qbert);
	m_Players.push_back(qbert);

#pragma endregion

#pragma region InitializeCoily
	SpawnEnemy(EnemyType::CoilyPlayer);
#pragma endregion
	InputManager::GetInstance().AddControlInput({ SDLK_q,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ SDLK_e,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ SDLK_a,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ SDLK_d,InputType::released,true }, std::make_shared<MoveCommand>(qbert, MoveDirection::bottomright));
}

void ManagerComponent::SpawnEnemy(EnemyType type)
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto creature = std::make_shared<GameObject>();
	switch (type)
	{
	case EnemyType::GreenEnemy:
		creature->AddComponent(std::make_shared<RenderComponent>(creature));
		creature->AddComponent(std::make_shared<GreenCreatureComponent>(creature, m_pGrid, std::vector<std::string>{"Sam.png","Slick.png"}));
		scene.lock()->Add(creature);
		m_Enemies.push_back(creature);
		break;
	case EnemyType::purpleEnemy:
		creature->AddComponent(std::make_shared<RenderComponent>(creature));
		creature->AddComponent(std::make_shared<PurpleCreatureComponent>(creature, m_pGrid, std::vector<std::string>{"WrongWay.png", "Ugg.png"}));
		scene.lock()->Add(creature);
		m_Enemies.push_back(creature);
		break;
	case EnemyType::Coily:
		creature->AddComponent(std::make_shared<RenderComponent>(creature));
		creature->GetComponent<RenderComponent>().lock()->SetTexture("Coily1.png");
		creature->AddComponent(std::make_shared<CoilyComponent>(creature,m_Players[0],m_pGrid,"Coily2.png"));
		scene.lock()->Add(creature);
		m_Enemies.push_back(creature);
		break;
	case EnemyType::CoilyPlayer:
		creature->AddComponent(std::make_shared<RenderComponent>(creature));
		creature->GetComponent<RenderComponent>().lock()->SetTexture("Coily1.png");
		creature->AddComponent(std::make_shared<CoilyComponent>(creature, m_Players[0], m_pGrid, "Coily2.png",false));
		scene.lock()->Add(creature);
		m_Enemies.push_back(creature);

		InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPLEFT,InputType::released,false }, std::make_shared<MoveCommand>(creature, MoveDirection::topleft, false));
		InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPRIGHT,InputType::released,false }, std::make_shared<MoveCommand>(creature, MoveDirection::topright, false));
		InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNLEFT,InputType::released,false }, std::make_shared<MoveCommand>(creature, MoveDirection::bottomleft, false));
		InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNRIGHT,InputType::released,false }, std::make_shared<MoveCommand>(creature, MoveDirection::bottomright, false));
		break;
	}
}

void ManagerComponent::HandleEnemyCollisions()
{
	for (auto enemy : m_Enemies)
	{
		for (auto player : m_Players)
		{
			if (!enemy.lock()->GetComponent<GreenCreatureComponent>().expired())
			{
				auto playerPos = player->GetComponent<PlayerComponent>().lock()->GetCurrentGridPos();
				auto enemyPos = enemy.lock()->GetComponent<GreenCreatureComponent>().lock()->GetCurrentGridPos();
				if (playerPos == enemyPos)
				{
					player->GetComponent<StatsComponent>().lock()->ChangeScore(300);
					enemy.lock()->SetIsActive(false);
				}
					
			}
			if (!enemy.lock()->GetComponent<PurpleCreatureComponent>().expired())
			{
				auto playerPos = player->GetComponent<PlayerComponent>().lock()->GetCurrentGridPos();
				auto enemyPos = enemy.lock()->GetComponent<PurpleCreatureComponent>().lock()->GetCurrentGridPos();

				auto IsOnDisk = player->GetComponent<PlayerComponent>().lock()->IsOnDisk();
				if (playerPos == enemyPos && !IsOnDisk)
				{
					player->GetComponent<PlayerComponent>().lock()->Kill(); //clear all enemies
					RemoveAllEnemies();
				}

			}
			if (!enemy.lock()->GetComponent<CoilyComponent>().expired())
			{
				auto playerPos = player->GetComponent<PlayerComponent>().lock()->GetCurrentGridPos();
				auto enemyPos = enemy.lock()->GetComponent<CoilyComponent>().lock()->GetCurrentGridPos();

				auto IsOnDisk = player->GetComponent<PlayerComponent>().lock()->IsOnDisk();
				if (playerPos == enemyPos && !IsOnDisk)
				{
					player->GetComponent<PlayerComponent>().lock()->Kill(); //clear all enemies
					RemoveAllEnemies();
				}

			}
		}
	}
}

void ManagerComponent::RemoveInactiveEnemies()
{
	m_Enemies.erase(std::remove_if(m_Enemies.begin(), m_Enemies.end(), [](std::weak_ptr<GameObject>& s) {return s.expired(); }), m_Enemies.end());
}

void ManagerComponent::RemoveAllEnemies()
{
	for (auto enemy : m_Enemies)
		if (!enemy.expired())
			enemy.lock()->SetIsActive(false);
}
