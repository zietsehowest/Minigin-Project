#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <map>
#include "BaseComponent.h"
#include "MiniginPCH.h"
#include "RenderComponent.h"
namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update(float) override;
		void Render() const override;

		void SetPosition(float x, float y);

		bool AddComponent(const ComponentType& type);
		
		std::map<ComponentType, std::shared_ptr<BaseComponent>> GetComponents() const; //why can't this be inline ?


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		inline std::shared_ptr<T> GetComponent(const ComponentType& CompType)
		{
			auto component = std::dynamic_pointer_cast<T>(m_Components.at(CompType));
			return component;
		}

	private:
		Transform m_Transform;
		std::map<ComponentType, std::shared_ptr<BaseComponent>> m_Components;
	};
}
