#include "MiniginPCH.h"
#include "GameAudio.h"
using namespace GameEngine;
GameAudio::GameAudio()
	:m_Thread(&GameAudio::Update,this)
{
	
}
GameAudio::~GameAudio()
{
	for (auto audioPair : m_pMixChunks)
	{
		Mix_FreeChunk(audioPair.second);
		audioPair.second = nullptr;
	}
	m_Quit = true;
	m_Condition.notify_one();
	m_Thread.join();
}
bool GameAudio::Play(const std::string& soundName, int loop)
{
	auto it = std::find_if(m_pMixChunks.begin(), m_pMixChunks.end(), [soundName](const AudioPair& a) {return a.first == soundName; });
	if (it != m_pMixChunks.end())
	{
		m_Queue.push(std::make_pair(soundName, loop));
		return true;
	}
	else
		return false;
}
void GameAudio::Update()
{
	while (!m_Quit)
	{
		//hold program until we can lock mutex
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock, [this] {return (!m_Queue.empty() || !m_Quit); }); //wait until we have a song in the queue

		//we can now use this lock without causing the thread to interfere with other threads
		if (!m_Queue.empty())
		{
			Mix_PlayChannel(-1, m_pMixChunks[m_Queue.front().first], m_Queue.front().second);
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
void GameAudio::SetVolume(const std::string& sound,int value)
{
	if (m_pMixChunks[sound] != nullptr)
		Mix_VolumeChunk(m_pMixChunks[sound],value);
}
int GameAudio::GetVolume(const std::string& sound) const
{
	if (m_pMixChunks.at(sound) != nullptr)
		return Mix_VolumeChunk(m_pMixChunks.at(sound), -1);
	else
		return -1;
}

bool GameEngine::GameAudio::AddSound(const std::string& soundName, const std::string& soundPath)
{
	auto it = std::find_if(m_pMixChunks.begin(), m_pMixChunks.end(), [soundName](const AudioPair& a) {return a.first == soundName; });
	if (it != m_pMixChunks.end())
		return false;
	else
	{
		auto tempChunk = Mix_LoadWAV(soundPath.c_str());

		if (tempChunk == nullptr)
		{
			std::string errorMsg = "SoundEffect: Failed to load " + soundPath + ",\nSDL_mixer Error: " + Mix_GetError();
			std::cerr << errorMsg;
			return false;
		}
		m_pMixChunks.emplace(soundName, tempChunk);
		return true;
	}
}

