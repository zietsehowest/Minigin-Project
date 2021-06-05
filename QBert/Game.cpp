#include "Game.h"
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

using namespace std;
using namespace std::chrono;
using namespace GameEngine;
void Game::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");

	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("background.jpg");
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

#pragma region QBert
	//lives display
	auto lives = std::make_shared<GameObject>();
	lives->AddComponent(std::make_shared<TextComponent>(lives));
	lives->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,140,0 });
	lives->SetPosition(30, 30);
	scene.Add(lives);

	//score display
	auto score = std::make_shared<GameObject>();
	score->AddComponent(std::make_shared<TextComponent>(score));
	score->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,140,0 });
	score->SetPosition(30, 70);
	scene.Add(score);

	//adding grid
	auto grid = std::make_shared<GameObject>();
	grid->AddComponent(std::make_shared<GridComponent>(grid, "../Data/Grid/GridInfo_lvl1.txt"));
	scene.Add(grid);

	//Creating the Q*Bert
	auto QBert = std::make_shared<GameObject>();
	QBert->AddComponent(std::make_shared<RenderComponent>(QBert));
	QBert->GetComponent<RenderComponent>().lock()->SetTexture("QBertMain.png");
	QBert->AddComponent(std::make_shared<StatsComponent>(QBert, 3));
	QBert->AddComponent(std::make_shared<SubjectComponent>(QBert));
	QBert->AddComponent(std::make_shared<PlayerComponent>(QBert, grid));
	QBert->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives->GetComponent<TextComponent>(), score->GetComponent<TextComponent>()));
	scene.Add(QBert);

	//Adding test Coily
	auto Coily = std::make_shared<GameObject>();
	Coily->AddComponent(std::make_shared<RenderComponent>(Coily));
	Coily->GetComponent<RenderComponent>().lock()->SetTexture("Coily1.png");
	Coily->AddComponent(std::make_shared<CoilyComponent>(Coily,QBert,grid,"Coily2.png"));
	scene.Add(Coily);

	//Adding test ugg and wrongway
	auto wrongway = std::make_shared<GameObject>();
	wrongway->AddComponent(std::make_shared<RenderComponent>(wrongway));
	wrongway->AddComponent(std::make_shared<PurpleCreatureComponent>(wrongway, grid,EnemyType::wrongway,std::vector<std::string>{"WrongWay.png","Ugg.png"}));
	scene.Add(wrongway);

	auto ugg = std::make_shared<GameObject>();
	ugg->AddComponent(std::make_shared<RenderComponent>(ugg));
	ugg->AddComponent(std::make_shared<PurpleCreatureComponent>(ugg, grid, EnemyType::ugg, std::vector<std::string>{"WrongWay.png", "Ugg.png"}));
	scene.Add(ugg);

	//Adding test to slick and sam
	auto creature = std::make_shared<GameObject>();
	creature->AddComponent(std::make_shared<RenderComponent>(creature));
	creature->AddComponent(std::make_shared<GreenCreatureComponent>(creature, grid, std::vector<std::string>{"Sam.png","Slick.png"}));
	scene.Add(creature);

#pragma endregion QBertInitialize

#pragma region Player2
	/*lives display
	auto lives2 = std::make_shared<GameObject>();
	lives2->AddComponent(std::make_shared<TextComponent>(lives2));
	lives2->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,0,0 });
	lives2->SetPosition(430, 370);
	scene.Add(lives2);

	score display
	auto score2 = std::make_shared<GameObject>();
	score2->AddComponent(std::make_shared<TextComponent>(score2));
	score2->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,0,0 });
	score2->SetPosition(430, 420);
	scene.Add(score2);
*/
#pragma endregion Player2Initialize

	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPLEFT,InputType::released,false}, std::make_shared<MoveCommand>(QBert,MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UPRIGHT,InputType::released,false}, std::make_shared<MoveCommand>(QBert, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNLEFT,InputType::released,false}, std::make_shared<MoveCommand>(QBert, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWNRIGHT,InputType::released,false}, std::make_shared<MoveCommand>(QBert, MoveDirection::bottomright));


	InputManager::GetInstance().AddControlInput({ SDLK_q,InputType::released,true }, std::make_shared<MoveCommand>(QBert, MoveDirection::topleft));
	InputManager::GetInstance().AddControlInput({ SDLK_e,InputType::released,true }, std::make_shared<MoveCommand>(QBert, MoveDirection::topright));
	InputManager::GetInstance().AddControlInput({ SDLK_a,InputType::released,true }, std::make_shared<MoveCommand>(QBert, MoveDirection::bottomleft));
	InputManager::GetInstance().AddControlInput({ SDLK_d,InputType::released,true }, std::make_shared<MoveCommand>(QBert, MoveDirection::bottomright));
	//InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_UP,InputType::released }, std::make_shared<ColorChangeCommand>(player2));
	//InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_DOWN,InputType::released }, std::make_shared<flyingDiscCoilyCommand>(player2));
	//InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_LEFT,InputType::released }, std::make_shared<endOfStageCommand>(player2));
	//InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_RIGHT,InputType::released }, std::make_shared<CatchingSlickAndSamCommand>(player2));

	//InputManager::GetInstance().AddControlInput({ VK_PAD_A,InputType::released }, std::make_shared<Killcommand>(player2));

	/*ServiceLocator::provide(new AudioLogger(new GameAudio()));
	auto t1 = ServiceLocator::getAudio();
	t1->AddSound("DeathSound", "../Data/Q-bert_Death_Sound.wav");
	t1->Play("DeathSound", 1);*/
}
