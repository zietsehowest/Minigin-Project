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
			return InputKey < temp.InputKey;
		}
		bool operator > (const KeyInput& temp) const
		{
			return InputKey > temp.InputKey;
		}
		bool operator == (const KeyInput& temp) const
		{
			return InputKey == temp.InputKey && inputType == temp.inputType;
		}
		int InputKey;
		InputType inputType;
		bool IsKeyBoardInput;
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		
		void AddControlInput(KeyInput key, const std::shared_ptr<Command>& command);
		
		bool IsKeyPressed(int keyId) const;
	private:
		XINPUT_KEYSTROKE m_KeyStroke{};

		std::map<KeyInput, std::shared_ptr<Command>> m_ControlCommands{};
	};

}
