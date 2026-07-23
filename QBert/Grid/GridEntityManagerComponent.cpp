#include "GridEntityManagerComponent.h"

#include "GridComponent.h"
#include "GridEntityComponent.h"
#include "GridMovementComponent.h"

qbert::GridEntityManagerComponent::GridEntityManagerComponent(dae::GameObject& owner, qbert::GridComponent& grid) :
	ObjectComponent(owner), m_pGrid(&grid)
{}

bool qbert::GridEntityManagerComponent::RequestMove(GridEntityComponent* entity, glm::ivec2 direction)
{
	const auto movementComponent = entity->GetMovement();
	const auto tileIndex = movementComponent->GetCurrentTileIndex();

	bool result{};

	if (auto target = tileIndex + direction; m_pGrid->IsValidTileIndex(target) && !movementComponent->IsMoving()) {
		movementComponent->MoveBetweenTiles(tileIndex,target);
		result = true;
	}
	return result;
}
