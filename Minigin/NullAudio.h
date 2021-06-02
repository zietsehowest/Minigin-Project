#pragma once
#include "Audio.h"
namespace GameEngine
{
	class NullAudio : public Audio
	{
	public:
		virtual bool Play(const std::string&, int) override { return false;/* Empty body */ };
		virtual void Stop(int) override { /* Empty body */ };
		virtual void StopAllSounds() { /* Empty body */ };
		virtual void SetVolume(const std::string&,int) { /* Empty body */ };
		virtual int GetVolume(const std::string&) const { return 0;/* Empty body */ };
		virtual bool AddSound(const std::string&, const std::string&) { return 0; }
	};
}
