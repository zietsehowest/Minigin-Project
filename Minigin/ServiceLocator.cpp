#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "NullAudio.h"
#include "Audio.h"
GameEngine::NullAudio GameEngine::ServiceLocator::m_NullService{};
GameEngine::Audio* GameEngine::ServiceLocator::m_Service = &m_NullService;
GameEngine::Audio* GameEngine::ServiceLocator::getAudio()
{
	return m_Service;
}
void GameEngine::ServiceLocator::provide(Audio* service)
{
	m_Service = service;
}