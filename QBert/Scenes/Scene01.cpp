#include "Scene01.h"

#include <Components/RenderComponent.h>
#include "../Player/PlayerControllerComponent.h"
#include "../Grid/GridComponent.h"
#include "../Grid/GridEntityComponent.h"
#include "../Grid/GridEntityManagerComponent.h"
#include "../Grid/GridInteractionComponent.h"
#include "../Grid/GridMovementComponent.h"


void qbert::Scene01::Load()
{

	const auto background = CreateGameObject();
	{
		auto renderComponent = background->AddComponent<dae::RenderComponent>("background.png");
		renderComponent->SetDestinationRectangle(0, 0, 1444,800);
	}

	const auto grid = CreateGameObject();
	grid->GetTransform()->SetLocalPosition(400, 200, 0);
	auto gridComponent = grid->AddComponent<qbert::GridComponent>("Data/Maps/Map01.json");
	auto gridEntityManagerComponent = grid->AddComponent<qbert::GridEntityManagerComponent>(*gridComponent);

	
	const auto player = CreateGameObject();
	{
		player->GetTransform()->SetLocalPosition(100, 100, 0);
		auto renderComponent = player->AddComponent<dae::RenderComponent>("Qbert P1 Spritesheet.png");
		renderComponent->SetSourceRectangle(0, 0, 16, 16);
		renderComponent->SetDestinationRectangle(0, 0, 32, 32);
		player->AddComponent<qbert::PlayerControllerComponent>();
		player->AddComponent<qbert::GridEntityComponent>(*gridEntityManagerComponent);
		player->AddComponent<qbert::GridMovementComponent>(*gridComponent);
		player->AddComponent<qbert::GridInteractionComponent>();
	}

	 
	//gridComp->AttachToGrid(player,0,0);

}
