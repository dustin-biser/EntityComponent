//
// AssetDefinitions.cpp
//
#include "AssetDefinitions.hpp"

namespace Asset
{

Asset::Definition Cannon =
R"(
id Cannon
vert -1.0 0.0
vert 1.0 0.0
vert 0.0 1.0
edge 0 2
edge 0 1
edge 1 2
)";


Asset::Definition Clock =
R"(
id ClockBase
vert -1.0 -1.0
vert 1.0 -1.0
vert 1.0 1.0
vert -1.0 1.0
edge 0 1
edge 1 2
edge 2 3
edge 3 0

id HourHand
parent ClockBase
vert 0.0 0.6
edge 0 1

id MinuteHand
parent ClockBase
vert 0.0 0.9
edge 0 1

id SecondHand
parent ClockBase
vert 0.0 0.85
edge 0 1
)";


Asset::Definition Projectile =
R"(
id Projectile
vert 0.2 -0.1
vert 0.2 0.3
vert -0.2 -0.3
vert -0.2 0.1
edge 0 1
edge 2 3
)";


} // end namespace Asset
