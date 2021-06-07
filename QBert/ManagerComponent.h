#pragma once
#include <MiniginPCH.h>
#include <BaseComponent.h>
namespace GameEngine
{
	enum class GameLevel {
		lvl1,lvl2,lvl3
	};
	enum class Gamemode {
		singleplayer,coop,versus
	};
	enum class EnemyType {
		purpleEnemy,GreenEnemy,Coily,CoilyPlayer
	};
	class ManagerComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		ManagerComponent(std::shared_ptr<GameObject> parent, Gamemode mode);
		virtual ~ManagerComponent() = default;
		ManagerComponent(const ManagerComponent& other) = delete;
		ManagerComponent(ManagerComponent&& other) = delete;
		ManagerComponent& operator=(const ManagerComponent& other) = delete;
		ManagerComponent& operator=(ManagerComponent&& other) = delete;

	private:
		std::vector<std::shared_ptr<GameObject>> m_Players;
		std::vector<std::weak_ptr<GameObject>> m_Enemies;
		std::weak_ptr<GameObject> m_pGrid;
		Gamemode m_CurrentGamemode;
		GameLevel m_CurrentLevel;
		bool m_HasCompletedLevel;
		bool m_testSpawn =true;
		float m_SpawnTimer;
		float m_MaxSpawnTimer;

		void InitializeSinglePlayer();
		void InitializeCoop();
		void InitializeVersus();

		void SpawnEnemies(float elapsedSec);

		void HandleEnemyCollisions();

		void RemoveInactiveEnemies();
		void RemoveAllEnemies();
		void ResetGame();

		void SpawnEnemy(EnemyType type);

		bool HasCoilyInlevel();



	};
}


