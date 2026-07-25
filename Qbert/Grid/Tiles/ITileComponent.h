#pragma once

#include <Components/ObjectComponent.h>

namespace qbert 
{
	class ITileComponent : public dae::ObjectComponent 
	{
	public:
		explicit ITileComponent(dae::GameObject& owner) :
			dae::ObjectComponent(owner)
		{}
		virtual ~ITileComponent() = default;

		virtual void OnTileEnter() = 0;
		virtual void OnTileExit() = 0;
	};
}
