#include "GridEntityManagerComponent.h"

#include "GridComponent.h"
#include "GridEntityComponent.h"

qbert::GridEntityManagerComponent::GridEntityManagerComponent(dae::GameObject& owner, qbert::GridComponent& grid) :
	ObjectComponent(owner), m_pGrid(&grid)
{}

void qbert::GridEntityManagerComponent::RequestMove(GridEntityComponent* entity, glm::ivec2 direction)
{
	direction;
	entity;
}
