#pragma once
#include "Audio.h"
namespace GameEngine
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
		virtual bool Play(const std::string& soundName, int loop) override
		{
			log("Play Sound");
			return m_WrappedAudio->Play(soundName, loop);
		}
		virtual bool AddSound(const std::string& soundName, const std::string& soundPath) override
		{
			log("Adding Sound");
			return m_WrappedAudio->AddSound(soundName, soundPath);
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
		virtual void SetVolume(const std::string& sound, int value)
		{
			log("Setting volume of sound");
			m_WrappedAudio->SetVolume(sound,value);
		}
		virtual int GetVolume(const std::string& sound) const
		{
			log("Getting the volume of the sound");
			return m_WrappedAudio->GetVolume(sound);
		}
	private:
		void log(const char* message) const
		{
			std::cout << message << std::endl;
		}
		Audio* m_WrappedAudio;
	};
}
