#pragma once
#include "GameMode.h"
#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>

#include <vector>

namespace qbert
{
	class Level {	
	private:
		std::vector<std::unique_ptr<dae::GameObject>> m_gameobjects;
	public:
		virtual ~Level() = default;
		virtual void Load(dae::Scene& scene, GameMode mode = GameMode::SinglePlayer) = 0;
	};
}