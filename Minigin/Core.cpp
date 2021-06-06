#include "MiniginPCH.h"
#include "Core.h"
#include <chrono>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <vld.h>
#include "ServiceLocator.h"
#include "Audio.h"
#include "GameAudio.h"
using namespace std;
using namespace std::chrono;
using namespace GameEngine;
void GameEngine::Core::Initialize()
{
	srand((int)time(nullptr));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}

	//Initialize SDL_Mixer
	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
	{
		std::cerr << "SDL Mixer failed to initialize! Cause of the error: " << Mix_GetError();
	}

	m_Window = SDL_CreateWindow(
		"QBird Game - Boonen Zietse",
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
void GameEngine::Core::LoadGame() const
{
	
}

void GameEngine::Core::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	
	if (ServiceLocator::getAudio())
		delete ServiceLocator::getAudio();
}

void GameEngine::Core::Run()
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
