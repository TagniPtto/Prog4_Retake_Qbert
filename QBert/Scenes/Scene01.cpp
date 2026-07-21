#include "Scene01.h"

#include <Components/RenderComponent.h>
#include "../Player/PlayerControllerComponent.h"


void qbert::Scene01::Initialize()
{
	const auto object = CreateGameObject();
	object->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
	object->AddComponent<qbert::PlayerControllerComponent>();

	object->GetTransform()->SetLocalPosition(100,100,0);

}
