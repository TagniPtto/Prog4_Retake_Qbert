#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "Levels/LevelManager.h"
#include "Levels/Level01.h"

#include "Player/PlayerControllerComponent.h"
#include "Grid/GridMovementComponent.h"
#include "Grid/GridInteractionComponent.h"
#include "Grid/GridComponent.h"
#include <SceneSystem/SceneManager.h>
#include <ServiceLocator.h>
#include <filesystem>

#include "Scenes/Scene01.h"

namespace fs = std::filesystem;

static void load()
{
	//qbert::LevelManager::Get().AddLevel(std::make_unique<qbert::Level01>());
	//qbert::LevelManager::Get().Load(0);

	auto& sceneManager = dae::ServiceLocator<dae::SceneManager>::Get();
	sceneManager.AddScene(std::make_unique<qbert::Scene01>());
	if (!sceneManager.LoadScene(0)) 
	{
		
	}
}


int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif

	dae::Minigin engine(data_location);
	engine.Run(load);
	
	return 0;
}
