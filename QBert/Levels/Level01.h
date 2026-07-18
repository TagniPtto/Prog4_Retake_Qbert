#include "Level.h"

namespace qbert {
	class Level01 : public Level{
	public:
		~Level01() = default;
		void Load(dae::Scene& scene , GameMode mode);
	};
}