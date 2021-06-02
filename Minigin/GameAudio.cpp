#include "MiniginPCH.h"
#include "GameAudio.h"
using namespace GameEngine;
GameAudio::GameAudio(const std::string& path)
	:m_Thread(&GameAudio::Update,this)
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
	m_Quit = true;
	m_Condition.notify_one();
	m_Thread.join();
}
bool GameAudio::Play(int soundID, int loop)
{
	if (m_pMixChunk != nullptr)
	{
		m_Queue.push(std::make_pair(soundID, loop));
		return true;
	}
	else
		return false;
}
void GameAudio::Update()
{
	while (m_Quit)
	{
		//hold program until we can lock mutex
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock, [this] {return (!m_Queue.empty() || !m_Quit); }); //wait until we have a song in the queue

		//we can now use this lock without causing the thread to interfere with other threads
		if (!m_Queue.empty())
		{
			Mix_PlayChannel(m_Queue.front().first, m_pMixChunk, m_Queue.front().second);
			m_Queue.pop();
		}

		//we are doing playing the sound unlock the lock/thread for a new sound to play
		lock.unlock();
	}
	
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

