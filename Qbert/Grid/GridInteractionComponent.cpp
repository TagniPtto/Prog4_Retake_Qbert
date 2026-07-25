#include "GridInteractionComponent.h"
#include "GridMovementComponent.h"
#include "GridEntityComponent.h"
#include "GridEntityManagerComponent.h"
#include "GridComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Utils.h>

qbert::GridInteractionComponent::GridInteractionComponent(dae::GameObject& owner):
	dae::ObjectComponent(owner)
{
}

void qbert::GridInteractionComponent::Start()
{
	if (auto gridComponent = GetOwner()->GetComponent<GridMovementComponent>(); gridComponent) 
	{
		gridComponent->OnMoveEntered.AddListener(std::bind(&GridInteractionComponent::OnMoveEnter, this, std::placeholders::_1));
		gridComponent->OnMoveExited.AddListener(std::bind(&GridInteractionComponent::OnMoveExit, this, std::placeholders::_1));
	}else{
		LOGLN("No MovementComponent on this object");
	}
	m_pEntityComponent = GetOwner()->GetComponent<GridEntityComponent>();
}

void qbert::GridInteractionComponent::OnMoveEnter(const MoveEvent& event)
{
	LOGLN("Entering Move");
	const auto manager = m_pEntityComponent->GetEntityManager();

	auto entities = manager->GetEntitiesAt(event.exitedTile);
	auto tile = manager->GetGridComponent()->GetTile(event.exitedTile);

	tile->OnTileExit();

	for (auto& entity : entities) 
	{
		entity->GetInteration()->OnOverlapExit(OverlapEvent{m_pEntityComponent , event.exitedTile});
	}
}

void qbert::GridInteractionComponent::OnMoveExit(const MoveEvent & event)
{
	LOGLN("Exiting Move");
	const auto manager = m_pEntityComponent->GetEntityManager();

	auto entities = manager->GetEntitiesAt(event.enteredTile);
	auto tile = manager->GetGridComponent()->GetTile(event.enteredTile);

	tile->OnTileEnter();

	for (auto& entity : entities)
	{
		entity->GetInteration()->OnOverlapEnter(OverlapEvent{ m_pEntityComponent , event.enteredTile });
	}
}

void qbert::GridInteractionComponent::OnOverlapEnter(const OverlapEvent& )
{
	LOGLN("OverlapEntering");
}

void qbert::GridInteractionComponent::OnOverlapExit(const OverlapEvent & )
{

	LOGLN("OverlapExiting");
}
