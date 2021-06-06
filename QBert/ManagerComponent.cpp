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
{
	switch (mode)
	{
	case Gamemode::singleplayer:
		InitializeSinglePlayer();
		break;
	case Gamemode::coop:
		InitializeCoop();
		break;
	case Gamemode::versus:
		InitializeVersus();
		break;
	}
}
void ManagerComponent::Update(float elapsedSec)
{

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
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_lvl2.txt",m_CurrentGamemode,GameLevel::lvl2));
	scene->Add(grid);

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
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_lvl2.txt",m_CurrentGamemode,GameLevel::lvl2));
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

}