#include "GridTileComponent.h"
#include <Utils.h>

qbert::GridTileComponent::GridTileComponent(dae::GameObject& owner):
	ITileComponent(owner)
{
}

void qbert::GridTileComponent::Start()
{}

void qbert::GridTileComponent::OnTileEnter()
{
	LOGLN("Entering GridTile");
}

void qbert::GridTileComponent::OnTileExit()
{
	LOGLN("Exiting GridTile");
}
