#include "Game.h"
#include "MiniginPCH.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "CharacterObserver.h"
#include "Observer.h"
#include "ManagerComponent.h"
#include "Audio.h"
#include "GameAudio.h"
#include "ServiceLocator.h"
#include "StartScreenComponent.h"
#pragma endregion
using namespace std;
using namespace GameEngine;
void Game::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("startscreen");

	auto go = std::make_shared<GameObject>();

	go->AddComponent(std::make_shared<StartScreenComponent>(go));
	go->AddComponent(std::make_shared<RenderComponent>(go));
	go->GetComponent<RenderComponent>().lock()->SetTexture("../Data/startScreen_Background.png");
	scene.Add(go);


	ServiceLocator::provide(new GameAudio());
	auto Audio = ServiceLocator::getAudio();
	
	Audio->AddSound("Disk_Taken","../Data/Sound/Disk_Taken.mp3");
	Audio->SetVolume("Disk_Taken", 5);

	Audio->AddSound("Level_Complete","../Data/Sound/Level_Complete.mp3");
	Audio->SetVolume("Level_Complete", 5);

	Audio->AddSound("Enemy_Jump","../Data/Sound/Enemy_jump.mp3");
	Audio->SetVolume("Enemy_Jump", 3);

	Audio->AddSound("Qbert_Death","../Data/Sound/Qbert_Death.wav");
	Audio->SetVolume("Qbert_Death", 5);

	Audio->AddSound("Qbert_Jump","../Data/Sound/Qbert_jump.mp3");
	Audio->SetVolume("Qbert_Jump", 5);
	
}
