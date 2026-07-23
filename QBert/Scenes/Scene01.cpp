#include "Scene01.h"

#include <Components/RenderComponent.h>
#include "../Player/PlayerControllerComponent.h"
#include "../Grid/GridComponent.h"


void qbert::Scene01::Load()
{

	const auto background = CreateGameObject();
	background->AddComponent<dae::RenderComponent>("background.png");

	const auto player = CreateGameObject();
	player->GetTransform()->SetLocalPosition(100, 100, 0);
	auto renderComp = player->AddComponent<dae::RenderComponent>("Qbert P1 Spritesheet.png");
	renderComp->SetSourceRectangle(0, 0, 16, 16);
	renderComp->SetDestinationRectangle(0, 0, 32, 32);
	player->AddComponent<qbert::PlayerControllerComponent>();

	const auto grid = CreateGameObject();
	grid->GetTransform()->SetLocalPosition(400, 200, 0);
	grid->AddComponent<qbert::GridComponent>("Data/Maps/Map01.json");
	 //auto gridComp =
	//gridComp->AttachToGrid(player,0,0);

}
