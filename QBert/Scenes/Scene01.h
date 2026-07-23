

#include <SceneSystem/Scene.h>

namespace qbert
{
	class Scene01 : public dae::Scene 
	{
	public:
		Scene01() = default;
		virtual ~Scene01() = default;
		virtual void Load() override;
	};
}
