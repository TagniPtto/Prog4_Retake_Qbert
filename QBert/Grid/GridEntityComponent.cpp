#include "GridEntityComponent.h"
#include "GridEntityManagerComponent.h"


qbert::GridEntityComponent::GridEntityComponent(dae::GameObject& owner, GridEntityManagerComponent& manager,int index):
	dae::ObjectComponent(owner),m_pManager(&manager), m_index(index)
{

}

int qbert::GridEntityComponent::GetIndex()
{
	return m_index;
}

