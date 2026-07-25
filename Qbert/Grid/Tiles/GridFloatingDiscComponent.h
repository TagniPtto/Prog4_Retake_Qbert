#pragma once 

#include "ITileComponent.h"

namespace qbert 
{
	class GridFloatingDiscComponent : public ITileComponent
	{
	public:
		explicit GridFloatingDiscComponent(dae::GameObject& owner);
		virtual ~GridFloatingDiscComponent() = default;

		virtual void OnTileEnter() override;
		virtual void OnTileExit() override ;
	};
}