#pragma once
namespace dae
{
	class AudioSystem;
	class ServiceLocator final
	{
	public:
		static AudioSystem& get_audio_system() { return *_as_instance; }
		static void register_sound_system(AudioSystem* as) { _as_instance = as; }
	private:
		static  AudioSystem* _as_instance;
	};
	AudioSystem* ServiceLocator::_as_instance{};
}