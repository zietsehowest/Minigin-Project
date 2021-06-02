#pragma once
#include <vector>
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib,"XInput.lib")
#include "Singleton.h"
#include "Command.h"
#include <memory>
#include <map>
namespace GameEngine
{
	enum class InputType
	{
		pressed,
		released,
		hold
	};
	struct KeyInput
	{
		bool operator < (const KeyInput& temp) const
		{
			return controllerKey < temp.controllerKey;
		}
		bool operator > (const KeyInput& temp) const
		{
			return controllerKey > temp.controllerKey;
		}
		bool operator == (const KeyInput& temp) const
		{
			return controllerKey == temp.controllerKey && inputType == temp.inputType;
		}
		int controllerKey;
		InputType inputType;
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddControlInput(KeyInput key, const std::shared_ptr<Command>& command);
		bool IsKeyPressed(int keyId) const;
		bool ProcessKeyBoardInput();
	private:
		XINPUT_KEYSTROKE m_KeyStroke{};

		std::map<KeyInput, std::shared_ptr<Command>> m_ControlCommands{};
	};

}
