#pragma once
#include "ITileComponent.h"
#include <Components/SequenceComponent.h>


namespace qbert
{
	class GridTileComponent : public ITileComponent
	{
	public:
		explicit GridTileComponent(dae::GameObject& owner);
		virtual ~GridTileComponent() = default;

		virtual void Start() override;
		virtual void OnTileEnter() override;
		virtual void OnTileExit() override;

	private:
		dae::RenderComponent* m_pRenderComponent;
		dae::SequenceComponent* m_pSequenceComponent;
	};
}