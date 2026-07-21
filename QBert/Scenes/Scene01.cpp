#include "Scene01.h"

#include <Components/RenderComponent.h>
#include "../Player/PlayerControllerComponent.h"
#include "../GridComponent.h"


void qbert::Scene01::Initialize()
{
	{
		const auto object = CreateGameObject();
		object->GetTransform()->SetLocalPosition(100, 100, 0);
		object->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
		object->AddComponent<qbert::PlayerControllerComponent>();

	}

	{
		const auto object = CreateGameObject();
		object->GetTransform()->SetLocalPosition(400, 200, 0);
		//object->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
		object->AddComponent<qbert::GridComponent>("Data/Maps/Map01.json");
	}

}
