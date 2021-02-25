#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <map>
#include "BaseComponent.h"
#include "MiniginPCH.h"
#include "RenderComponent.h"
#include <algorithm>
namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update(float) override;
		void Render() const override;

		void SetPosition(float x, float y);

		template <typename T>
		inline bool AddComponent(std::shared_ptr<T> component)
		{
			if (!GetComponent<T>().expired())
			{
				std::cout << "Component already exists\n";
				return false;
			}	
			else
			{
				m_Components.push_back(component);
				return true;
			}
		}
		
		std::vector<std::shared_ptr<BaseComponent>> GetComponents() const; //why can't this be inline ?

		inline void SetIsActive(bool state) { m_IsActive = state; }

		inline bool GetIsActive() const { return m_IsActive; }

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		std::weak_ptr<T> GetComponent()
		{
			std::weak_ptr<T> temp;
			for (std::shared_ptr<BaseComponent> component : m_Components)
			{
				temp = std::dynamic_pointer_cast<T>(component);
				if (temp.lock() != nullptr)
					return temp;
			}
			/*std::for_each(begin(m_Components), end(m_Components), [temp](std::shared_ptr<BaseComponent> c) 
				{
					if (std::dynamic_pointer_cast<T>(c) != nullptr)
						temp = std::make_shared<T>(c);
				});*/
			return temp;
		}
	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
		bool m_IsActive = true;
	};
}
