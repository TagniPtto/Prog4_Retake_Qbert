#include "ITileComponent.h"

namespace qbert {
	class GridVoidComponent : public ITileComponent
	{
	public:
		explicit GridVoidComponent(dae::GameObject& owner);
		virtual ~GridVoidComponent() = default;

		virtual void OnTileEnter() override;
		virtual void OnTileExit() override;
	};
}
