#pragma once

#include <glm/vec2.hpp>

namespace qbert
{
    struct MoveEvent
    {
        glm::ivec2 exitedTile;
        glm::ivec2 enteredTile;
    };

    class GridEntityComponent;
    struct OverlapEvent 
    {
        GridEntityComponent* other;
        glm::ivec2 overlappingLocation;
    };
}
