#include "GridTileComponent.h"
#include <GameObject.h>
#include <Utils.h>

qbert::GridTileComponent::GridTileComponent(dae::GameObject& owner):
	ITileComponent(owner)
{
}

void qbert::GridTileComponent::Start()
{
	if (m_pSequenceComponent = GetOwner()->GetComponent<dae::SequenceComponent>(); !m_pSequenceComponent)
	{
		LOGLN("No MovementComponent on this object");
	}
}

void qbert::GridTileComponent::OnTileEnter()
{
	m_pSequenceComponent->SetFrame(1);
	LOGLN("Entering GridTile");
}

void qbert::GridTileComponent::OnTileExit()
{
	LOGLN("Exiting GridTile");
}
