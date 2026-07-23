#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "../ServiceLocator.h"

void dae::SceneManager::Start()
{
	if (const auto& scene = m_scenes[m_activeSceneIndex]; scene) {
		scene->Start();
	}
}

void dae::SceneManager::Update()
{
	if (const auto& scene = m_scenes[m_activeSceneIndex]; scene) {
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	if (const auto& scene = m_scenes[m_activeSceneIndex]; scene) {
		scene->Render();
	}
}

bool dae::SceneManager::LoadScene(unsigned int index)
{
	if (m_scenes.size() > index && index >= 0)
	{
		m_scenes[m_activeSceneIndex]->Load();
		m_activeSceneIndex = index;
		return true;
	}
	return false;
}

void dae::SceneManager::AddScene(std::unique_ptr<Scene> scene)
{
	m_scenes.push_back(std::move(scene));
}


dae::Scene* dae::SceneManager::GetScene(int index) const
{
	if (index < (int)m_scenes.size())
	{
		return m_scenes[index].get();
	}
	return nullptr;
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return GetScene(m_activeSceneIndex);
}
