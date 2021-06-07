#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>

void GameEngine::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window,GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void GameEngine::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();
	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_Renderer);
}
void GameEngine::Renderer::RenderCustomImguiUI()
{
}
void GameEngine::Renderer::RenderInstructionMenuUI()
{
	ImGui::Begin("Instructions");

	ImGui::TextColored((ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f), "Here are the controls to the commands for observer demo\n");
	
	ImGui::TextColored((ImVec4)ImColor::HSV(0.0f, 100.0f, 100.0f), "Player 1 Controls:\n");
	ImGui::Text("Kill: DPAD_UP\nColorChange: LTHUMB_UP\nFlyingDisc: LTHUMB_DOWN\nEndOfStage: LTHUMB_LEFT\nCatchingSlickAndSam: LTHUMB_RIGHT");

	ImGui::TextColored((ImVec4)ImColor::HSV(240.0f, 100.0f, 100.0f), "Player 2 Controls:\n");
	ImGui::Text("Kill: PAD_A\nColorChange: RTHUMB_UP\nFlyingDisc: RTHUMB_DOWN\nEndOfStage: RTHUMB_LEFT\nCatchingSlickAndSam: RTHUMB_RIGHT");
	
	ImGui::End();
}
void GameEngine::Renderer::RenderImguiDemo()
{
	ImGui::ShowDemoWindow(&m_ShowDemo);
}
void GameEngine::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void GameEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void GameEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

int GameEngine::Renderer::GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for(auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}
