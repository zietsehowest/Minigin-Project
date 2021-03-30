#pragma once
#include "MiniginPCH.h"
#include <memory>
namespace dae
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual bool Play(int soundID, int loop) const = 0;
		virtual void Stop(int soundID) = 0;
		virtual void StopAllSounds() = 0;
		virtual void SetVolume(int value) = 0;
		virtual int GetVolume() const = 0;
	};
}