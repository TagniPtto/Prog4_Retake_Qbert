#include "GridVoidComponent.h"

#include <Utils.h>

qbert::GridVoidComponent::GridVoidComponent(dae::GameObject& owner):
	ITileComponent(owner)
{}

void qbert::GridVoidComponent::OnTileEnter()
{
	LOGLN("Entering Void");
}

void qbert::GridVoidComponent::OnTileExit()
{
	LOGLN("Exiting Void");
}
