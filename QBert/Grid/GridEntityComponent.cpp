#include "GridEntityComponent.h"
#include "GridEntityManagerComponent.h"
#include "GridMovementComponent.h"
#include "GridInteractionComponent.h"

#include <Utils.h>



qbert::GridEntityComponent::GridEntityComponent(dae::GameObject& owner, GridEntityManagerComponent& manager):
	dae::ObjectComponent(owner),m_pManager(&manager) 
{

}
void qbert::GridEntityComponent::Start()
{
	if (m_pMovement = GetOwner()->GetComponent<GridMovementComponent>(); !m_pMovement) 
	{
		LOGLN("No Grid Movement Component on Object");
	}
	if (m_pInteraction = GetOwner()->GetComponent<GridInteractionComponent>(); !m_pInteraction)
	{

		LOGLN("No Grid Interaction componnet on this object");
	}
}
bool qbert::GridEntityComponent::RequestMove(glm::ivec2 direction)
{
	return 	m_pManager->RequestMove(this, direction);
}

qbert::GridMovementComponent* qbert::GridEntityComponent::GetMovement() const
{
	return m_pMovement;
}

qbert::GridInteractionComponent* qbert::GridEntityComponent::GetInteration() const
{
	return m_pInteraction;
}

