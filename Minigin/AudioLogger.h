#pragma once
#include "Audio.h"
namespace dae
{
	class AudioLogger : public Audio
	{
	public:
		AudioLogger(Audio* wrappedAudio)
			: m_WrappedAudio(wrappedAudio)
		{}
		virtual ~AudioLogger()
		{
			delete m_WrappedAudio;
		}
		virtual bool Play(int soundID, int loop) override
		{
			log("Play Sound");
			return m_WrappedAudio->Play(soundID, loop);
		}
		virtual void Stop(int soundID)
		{
			log("Stop Sound");
			m_WrappedAudio->Stop(soundID);
		}
		virtual void StopAllSounds()
		{
			log("Stop all sounds");
			m_WrappedAudio->StopAllSounds();
		}
		virtual void SetVolume(int value)
		{
			log("Setting volume of sound");
			m_WrappedAudio->SetVolume(value);
		}
		virtual int GetVolume() const
		{
			log("Getting the volume of the sound");
			return m_WrappedAudio->GetVolume();
		}
	private:
		void log(const char* message) const
		{
			std::cout << message << std::endl;
		}
		Audio* m_WrappedAudio;
	};
}
