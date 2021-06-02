#pragma once
#include "Audio.h"
namespace dae
{
	class NullAudio : public Audio
	{
	public:
		virtual bool Play(int, int) override { return false;/* Empty body */ };
		virtual void Stop(int) override { /* Empty body */ };
		virtual void StopAllSounds() { /* Empty body */ };
		virtual void SetVolume(int) { /* Empty body */ };
		virtual int GetVolume() const { return 0;/* Empty body */ };
	};
}
