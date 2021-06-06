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
#include "ManagerComponent.h"
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

	go->AddComponent<>(std::make_shared<ManagerComponent>(go, Gamemode::coop));
	scene.Add(go);

	////Adding test Coily
	//auto Coily = std::make_shared<GameObject>();
	//Coily->AddComponent(std::make_shared<RenderComponent>(Coily));
	//Coily->GetComponent<RenderComponent>().lock()->SetTexture("Coily1.png");
	//Coily->AddComponent(std::make_shared<CoilyComponent>(Coily,QBert,grid,"Coily2.png"));
	//scene.Add(Coily);

	////Adding test ugg and wrongway
	//auto wrongway = std::make_shared<GameObject>();
	//wrongway->AddComponent(std::make_shared<RenderComponent>(wrongway));
	//wrongway->AddComponent(std::make_shared<PurpleCreatureComponent>(wrongway, grid,EnemyType::wrongway,std::vector<std::string>{"WrongWay.png","Ugg.png"}));
	//scene.Add(wrongway);

	//auto ugg = std::make_shared<GameObject>();
	//ugg->AddComponent(std::make_shared<RenderComponent>(ugg));
	//ugg->AddComponent(std::make_shared<PurpleCreatureComponent>(ugg, grid, EnemyType::ugg, std::vector<std::string>{"WrongWay.png", "Ugg.png"}));
	//scene.Add(ugg);

	////Adding test to slick and sam
	//auto creature = std::make_shared<GameObject>();
	//creature->AddComponent(std::make_shared<RenderComponent>(creature));
	//creature->AddComponent(std::make_shared<GreenCreatureComponent>(creature, grid, std::vector<std::string>{"Sam.png","Slick.png"}));
	//scene.Add(creature);


}
