#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "NullAudio.h"
#include "Audio.h"
dae::NullAudio dae::ServiceLocator::m_NullService{};
dae::Audio* dae::ServiceLocator::m_Service = &m_NullService;
dae::Audio* dae::ServiceLocator::getAudio()
{
	return m_Service;
}
void dae::ServiceLocator::provide(Audio* service)
{
	m_Service = service;
}