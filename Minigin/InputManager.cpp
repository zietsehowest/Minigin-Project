#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool GameEngine::InputManager::ProcessInput()
{
	//Reading the input
	RtlSecureZeroMemory(&m_KeyStroke, sizeof(XINPUT_KEYSTROKE));

	//getting keyInput
	DWORD result = XInputGetKeystroke(0, 0, &m_KeyStroke);

	//with the keystroke input I can process all 3 InputTypes at the same time
	if (result == ERROR_SUCCESS)
	{
		for (std::pair<KeyInput, std::shared_ptr<Command>> comm : m_ControlCommands)
		{
			if (comm.first.controllerKey == m_KeyStroke.VirtualKey) //first check wheter the key that is pressed is linked to a command
			{
				switch (comm.first.inputType) //check what input type is linked with this key
				{
				case InputType::released:
					if (m_KeyStroke.Flags & XINPUT_KEYSTROKE_KEYUP)
						comm.second->Execute();
					break;
				case InputType::pressed:
					if (m_KeyStroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
						comm.second->Execute();
					break;
				case InputType::hold:
					if (m_KeyStroke.Flags & XINPUT_KEYSTROKE_REPEAT)
						comm.second->Execute();
					break;
				}
			}
		}
	}


	return ProcessKeyBoardInput();
}
bool GameEngine::InputManager::ProcessKeyBoardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYUP) //SDL Key test
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				std::cout << "Test Pressing A";
				return true;
			}
		}
	}
	return true;
}
void GameEngine::InputManager::AddControlInput(KeyInput key, const std::shared_ptr<Command>& command)
{
	m_ControlCommands[key] = command;
}
bool GameEngine::InputManager::IsKeyPressed(int keyId) const
{
	if (keyId == m_KeyStroke.VirtualKey)
	{
		if (m_KeyStroke.Flags & XINPUT_KEYSTROKE_KEYDOWN)
			return true;
	}
	return false;
}

