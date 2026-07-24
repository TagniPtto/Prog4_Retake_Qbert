#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../GameObject.h"
#include "../Application.h"

namespace dae
{
	class ObjectComponent;

	class Scene
	{
	private:
		std::vector<std::unique_ptr<GameObject>> m_objects{};
		ApplicationContext* m_pAppContext;
	public:

		explicit Scene(dae::ApplicationContext&);
		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		ApplicationContext* GetAppContext() const;
		GameObject* CreateGameObject();
	
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();
		void DestroyMarkedObjects();

		virtual void Load();
		virtual void Start();
		virtual void Update();
		virtual void Render() const;
		
		template<Component T>
		T* FindComponent() const;

	};



	template<Component T>
	inline T* Scene::FindComponent() const{
		T* comp{};
		for (auto& object : m_objects) {
			if (comp = object->GetComponent<T>(); comp) {
				break;
			}
		}
		return comp;
	}
}
