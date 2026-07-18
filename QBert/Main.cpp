#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "Levels/LevelManager.h"
#include "Levels/Level01.h"

#include "Player/PlayerControllerComponent.h"
#include "Player/PlayerStateComponent.h"
#include "GridMovementComponent.h"
#include "GridInteractionComponent.h"
#include "GridComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	qbert::LevelManager::Get().AddLevel(std::make_unique<qbert::Level01>());
	qbert::LevelManager::Get().Load(0);

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
