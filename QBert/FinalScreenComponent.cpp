#include "FinalScreenComponent.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>
#include "ManagerComponent.h"
#include "Scene.h"
using namespace GameEngine;
FinalScreenComponent::FinalScreenComponent(std::shared_ptr<GameObject> parent, std::string finalScreenText) : BaseComponent(parent)
{
	m_FinalString = finalScreenText;
}
void FinalScreenComponent::Update(float)
{
}
void FinalScreenComponent::Render(const Transform&) const
{
	static bool checkBox = false;
	static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
	ImGui::Begin("Window2", 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowPos(ImVec2{ 160,100 });
	ImGui::Text(m_FinalString.c_str());
	ImGui::PopStyleColor(1);
	ImGui::End();
}