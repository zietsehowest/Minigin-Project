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
#pragma endregion

#pragma region CommandIncludes
#include "KillCommand.h"
#include "flyingDiscCoilyCommand.h"
#include "CatchingSlickAndSamCommand.h"
#include "endOfStageCommand.h"
#include "ColorChangeCommand.h"
#pragma endregion

using namespace std;
using namespace std::chrono;
using namespace GameEngine;
void Game::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TextComponent>(go));
	go->GetComponent<TextComponent>().lock()->SetText("Programming 4 Assignment", font, SDL_Color{ 255,255,255 });
	go->SetPosition(90, 30);
	scene.Add(go);


	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<FPSComponent>(go));
	go->GetComponent<FPSComponent>().lock()->SetText("60", font, SDL_Color{ 255,0,0 });
	go->SetPosition(20, 20);
	scene.Add(go);

#pragma region QBert
	//lives display
	auto lives = std::make_shared<GameObject>();
	lives->AddComponent(std::make_shared<TextComponent>(lives));
	lives->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 0,0,255 });
	lives->SetPosition(90, 370);
	scene.Add(lives);

	//score display
	auto score = std::make_shared<GameObject>();
	score->AddComponent(std::make_shared<TextComponent>(score));
	score->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 0,0,255 });
	score->SetPosition(90, 420);
	scene.Add(score);

	//Creating the Q*Bert
	auto QBert = std::make_shared<GameObject>();
	QBert->AddComponent(std::make_shared<RenderComponent>(QBert));
	QBert->GetComponent<RenderComponent>().lock()->SetTexture("Qbert.png");
	QBert->AddComponent(std::make_shared<StatsComponent>(QBert, 3));
	QBert->AddComponent(std::make_shared<SubjectComponent>(QBert));
	QBert->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives->GetComponent<TextComponent>(), score->GetComponent<TextComponent>()));
	QBert->SetPosition(50, 150);
	scene.Add(QBert);
#pragma endregion QBertInitialize

#pragma region Player2
	//lives display
	auto lives2 = std::make_shared<GameObject>();
	lives2->AddComponent(std::make_shared<TextComponent>(lives2));
	lives2->GetComponent<TextComponent>().lock()->SetText("Lives: 3", font, SDL_Color{ 255,0,0 });
	lives2->SetPosition(430, 370);
	scene.Add(lives2);

	//score display
	auto score2 = std::make_shared<GameObject>();
	score2->AddComponent(std::make_shared<TextComponent>(score2));
	score2->GetComponent<TextComponent>().lock()->SetText("Score: 0", font, SDL_Color{ 255,0,0 });
	score2->SetPosition(430, 420);
	scene.Add(score2);

	//Creating the Player 2
	auto player2 = std::make_shared<GameObject>();
	player2->AddComponent(std::make_shared<RenderComponent>(player2));
	player2->GetComponent<RenderComponent>().lock()->SetTexture("Coily.png");
	player2->AddComponent(std::make_shared<StatsComponent>(player2, 3));
	player2->AddComponent(std::make_shared<SubjectComponent>(player2));
	player2->GetComponent<SubjectComponent>().lock()->AddObserver(std::make_shared<CharacterObserver>(lives2->GetComponent<TextComponent>(), score2->GetComponent<TextComponent>()));
	player2->SetPosition(400, 200);
	scene.Add(player2);
#pragma endregion Player2Initialize

	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_UP,InputType::released }, std::make_shared<ColorChangeCommand>(QBert));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_DOWN,InputType::released }, std::make_shared<flyingDiscCoilyCommand>(QBert));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_LEFT,InputType::released }, std::make_shared<endOfStageCommand>(QBert));
	InputManager::GetInstance().AddControlInput({ VK_PAD_LTHUMB_RIGHT,InputType::released }, std::make_shared<CatchingSlickAndSamCommand>(QBert));

	InputManager::GetInstance().AddControlInput({ VK_PAD_DPAD_UP,InputType::released }, std::make_shared<Killcommand>(QBert));

	InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_UP,InputType::released }, std::make_shared<ColorChangeCommand>(player2));
	InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_DOWN,InputType::released }, std::make_shared<flyingDiscCoilyCommand>(player2));
	InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_LEFT,InputType::released }, std::make_shared<endOfStageCommand>(player2));
	InputManager::GetInstance().AddControlInput({ VK_PAD_RTHUMB_RIGHT,InputType::released }, std::make_shared<CatchingSlickAndSamCommand>(player2));

	InputManager::GetInstance().AddControlInput({ VK_PAD_A,InputType::released }, std::make_shared<Killcommand>(player2));

	ServiceLocator::provide(new AudioLogger(new GameAudio()));
	auto t1 = ServiceLocator::getAudio();
	t1->AddSound("DeathSound", "../Data/Q-bert_Death_Sound.wav");
	t1->Play("DeathSound", 1);
}
