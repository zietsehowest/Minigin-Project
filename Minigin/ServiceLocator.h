#pragma once
namespace dae
{
	class Audio;
	class NullAudio;
	class ServiceLocator
	{
	public:
		static Audio* getAudio();
		static void provide(Audio* service);
	private:
		static Audio* m_Service;
		static NullAudio m_NullService;
	};
}