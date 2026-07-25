#include "GridFloatingDiscComponent.h"

#include <Utils.h>

qbert::GridFloatingDiscComponent::GridFloatingDiscComponent(dae::GameObject& owner):
	ITileComponent(owner)
{}

void qbert::GridFloatingDiscComponent::OnTileEnter()
{
	LOGLN("Entering Floating Disc");
}

void qbert::GridFloatingDiscComponent::OnTileExit()
{
	LOGLN("Exiting Floating Disc");
}
