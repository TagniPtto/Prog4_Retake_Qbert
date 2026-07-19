#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SceneSystem/Scene.h>


namespace dae
{
	class SceneManager final
	{
	public:
		~SceneManager() = default;

		bool LoadScene(unsigned int index);
		void AddScene(std::unique_ptr<Scene> scene);

		Scene* GetScene(int index) const;
		Scene* GetActiveScene() const;

		void Update();
		void Render();

	private:
		friend class Minigin;
		SceneManager() = default;

		unsigned int m_activeSceneIndex{};
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
