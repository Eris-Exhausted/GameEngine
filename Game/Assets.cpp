#include "Assets.h"

using namespace nu;

namespace assets
{
    Mesh ship(std::vector<Vector2>{Vector2(-3, -2), Vector2(2, 0), Vector2(-3, 2), Vector2(-1.5, 0), Vector2(-3, -2)},
        Vector3{ 255,255,255 });
    Mesh flame(std::vector<Vector2>{Vector2(-4, -0), Vector2(-5, 1), Vector2(-7, 0), Vector2(-5, -1), Vector2(-4, 0)},
        Vector3{ 255,0,0 });

    // Make this actually be the player model
	nu::Model playerModel;
}