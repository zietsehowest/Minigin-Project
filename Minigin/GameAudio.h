#pragma once
#include "MiniginPCH.h"
#include "Audio.h"
#include <thread>
#include <queue>
#include <mutex>
#include <map>
namespace GameEngine
{
	using AudioPair = std::pair<std::string, Mix_Chunk*>;
	class GameAudio : public Audio
	{
	public:
		GameAudio();
		virtual ~GameAudio();
		virtual bool Play(const std::string& soundName, int loop) override;
		virtual void Stop(int soundID) override;
		virtual void StopAllSounds();
		virtual void SetVolume(const std::string& sound,int value);
		virtual int GetVolume(const std::string& sound) const;
		virtual bool AddSound(const std::string& soundName, const std::string& soundPath);
	private:
		void Update();

		std::map<std::string,Mix_Chunk*> m_pMixChunks;
		std::thread m_Thread;
		std::queue<std::pair<std::string, int>> m_Queue;
		std::condition_variable m_Condition;
		std::mutex m_Mutex;
		bool m_Quit = false;
	};
}

