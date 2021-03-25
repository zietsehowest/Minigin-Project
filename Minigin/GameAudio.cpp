#include "MiniginPCH.h"
#include "GameAudio.h"
using namespace dae;
GameAudio::GameAudio(const std::string& path)
{
	m_pMixChunk = Mix_LoadWAV(path.c_str());

	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
}
GameAudio::~GameAudio()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}
bool GameAudio::Play(int soundID, int loop) const
{
	if (m_pMixChunk != nullptr)
	{
		int channel{ Mix_PlayChannel(soundID,m_pMixChunk,loop) };
		return channel == -1 ? false : true;
	}
	else
		return false;
}
void GameAudio::Stop(int soundID)
{
	Mix_HaltChannel(soundID);
}
void GameAudio::StopAllSounds()
{
	Mix_HaltChannel(-1);
}
void GameAudio::SetVolume(int value)
{
	if (m_pMixChunk != nullptr)
		Mix_VolumeChunk(m_pMixChunk,value);
}
int GameAudio::GetVolume() const
{
	if (m_pMixChunk != nullptr)
		return Mix_VolumeChunk(m_pMixChunk, -1);
	else
		return -1;
}

