#pragma once
#include <MiniginPCH.h>
#include <BaseComponent.h>
#include <GameObject.h>
#include <Texture2D.h>
namespace GameEngine
{
	class DiskComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedSec) override;
		virtual void Render(const Transform&) const {};

		DiskComponent(std::shared_ptr<GameObject> parent, IPoint2 diskCoordinates, float teleportCooldown = 3.f);
		virtual ~DiskComponent() = default;
		DiskComponent(const DiskComponent& other) = delete;
		DiskComponent(DiskComponent&& other) = delete;
		DiskComponent& operator=(const DiskComponent& other) = delete;
		DiskComponent& operator=(DiskComponent&& other) = delete;

		IPoint2 GetDiskCoordinates() { return m_Position; }

		void ActivateDisk(std::weak_ptr<GameObject> m_QBert);
	private:
		IPoint2 m_Position;
		std::weak_ptr<GameObject> m_Qbert;

		float m_TeleportCooldown;
		bool m_IsDiskActivated;
	};
}


