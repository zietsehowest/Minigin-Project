#include "StartScreenComponent.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>
#include "ManagerComponent.h"
#include "Scene.h"
using namespace GameEngine;
StartScreenComponent::StartScreenComponent(std::shared_ptr<GameObject> parent) : BaseComponent(parent)
{
}
void StartScreenComponent::Update(float)
{
}
void StartScreenComponent::Render(const Transform&) const
{
	static bool checkBox = false;
	static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
	ImGui::Begin("Window", 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowPos(ImVec2{ 160,100 });
	ImGui::Text("Gamemodes:");
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
	if (ImGui::Button("Single Player", ImVec2{300.f,100.f }))
	{
		auto& singlePlayer = SceneManager::GetInstance().CreateScene("SinglePlayer");
		SceneManager::GetInstance().SetCurrentScene("SinglePlayer");
		auto so = std::make_shared<GameObject>();
		so->AddComponent(std::make_shared<ManagerComponent>(so, Gamemode::singleplayer));
		singlePlayer.Add(so);
	}
	if (ImGui::Button("Coop", ImVec2{ 300.f,100.f }))
	{
		auto& coop = SceneManager::GetInstance().CreateScene("Coop");
		SceneManager::GetInstance().SetCurrentScene("Coop");
		auto so = std::make_shared<GameObject>();
		so->AddComponent(std::make_shared<ManagerComponent>(so, Gamemode::coop));
		coop.Add(so);
	}
	if(ImGui::Button("Versus", ImVec2{ 300.f,100.f }))
	{
		auto& versus = SceneManager::GetInstance().CreateScene("Versus");
		SceneManager::GetInstance().SetCurrentScene("Versus");
		auto so = std::make_shared<GameObject>();
		so->AddComponent(std::make_shared<ManagerComponent>(so, Gamemode::versus));
		versus.Add(so);
	}
	ImGui::PopStyleColor(1);
	ImGui::End();
}
