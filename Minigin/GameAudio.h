#pragma once
#include "MiniginPCH.h"
#include "Audio.h"
#include <thread>
#include <queue>
#include <mutex>
namespace dae
{
	class GameAudio : public Audio
	{
	public:
		GameAudio(const std::string& path);
		virtual ~GameAudio();
		virtual bool Play(int soundID, int loop) override;
		virtual void Stop(int soundID) override;
		virtual void StopAllSounds();
		virtual void SetVolume(int value);
		virtual int GetVolume() const;
	private:
		void Update();

		Mix_Chunk* m_pMixChunk;
		std::thread m_Thread;
		std::queue<std::pair<int, int>> m_Queue;
		std::condition_variable m_Condition;
		std::mutex m_Mutex;

		bool m_Quit = false;
	};
}

