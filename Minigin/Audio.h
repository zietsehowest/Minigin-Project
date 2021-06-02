#pragma once
#include "MiniginPCH.h"
#include <memory>
namespace GameEngine
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual bool Play(const std::string& soundName, int loop) = 0;
		virtual void Stop(int soundID) = 0;
		virtual void StopAllSounds() = 0;
		virtual void SetVolume(const std::string& sound,int value) = 0;
		virtual int GetVolume(const std::string& sound) const = 0;
		virtual bool AddSound(const std::string& soundName, const std::string& soundPath) = 0;
	};
}