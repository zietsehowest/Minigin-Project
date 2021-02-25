#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
using namespace std;
using namespace std::chrono;
using namespace dae;
void dae::Minigin::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
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
	go->GetComponent<TextComponent>().lock()->SetText("Programming 4 Assignment", font, SDL_Color{ 255,255,255});
	go->SetPosition(90, 30);
	scene.Add(go);

	
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<FPSComponent>(go));
	go->GetComponent<FPSComponent>().lock()->SetText("60", font, SDL_Color{ 255,0,0 });
	go->SetPosition(20, 20);
	scene.Add(go);

	//Creating the Q*Bert
	auto QBert = std::make_shared<GameObject>();
	QBert->AddComponent(std::make_shared<RenderComponent>(QBert));
	QBert->GetComponent<RenderComponent>().lock()->SetTexture("Qbert.png");
	QBert->SetPosition(50, 50);
	scene.Add(QBert);

	InputManager::GetInstance().AddControlInput({ VK_PAD_A,InputType::released }, std::make_shared<FireCommand>());
	InputManager::GetInstance().AddControlInput({ VK_PAD_B,InputType::released }, std::make_shared<DuckCommand>());
	InputManager::GetInstance().AddControlInput({ VK_PAD_X,InputType::released }, std::make_shared<JumpCommand>());
	InputManager::GetInstance().AddControlInput({ VK_PAD_Y,InputType::released }, std::make_shared<FartCommand>());
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now(); //get time before frame
		while (doContinue)
		{
			auto currentTime = high_resolution_clock::now(); //get time before all updates start of each fraem
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
			
			lastTime = currentTime;
		}
	}

	Cleanup();
}
