#pragma once
#include "MiniginPCH.h"
#include "Audio.h"
namespace dae
{
	class GameAudio : public Audio
	{
	public:
		GameAudio(const std::string& path);
		virtual ~GameAudio();
		virtual bool Play(int soundID, int loop) const override;
		virtual void Stop(int soundID) override;
		virtual void StopAllSounds();
		virtual void SetVolume(int value);
		virtual int GetVolume() const;
	private:
		Mix_Chunk* m_pMixChunk;
	};
}

