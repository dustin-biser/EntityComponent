//
// AssetDefinitions.cpp
//
#include "AssetDefinitions.hpp"

namespace Asset
{

Asset::Definition Cannon =
R"(
id Cannon
vert -0.5 0.0
vert 0.5 0.0
vert 0.0 1.0
edge 0 2
edge 0 1
edge 1 2
)";


Asset::Definition Projectile =
R"(
id Projectile
vert 0.0 -0.2
vert 0.0 0.2
edge 0 1
)";


Asset::Definition ClockBase =
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
)";

Asset::Definition HourHand =
R"(
id HourHand
vert 0.0 0.0
vert 0.0 0.45
edge 0 1
)";


Asset::Definition MinuteHand =
R"(
id MinuteHand
vert 0.0 0.0
vert 0.0 0.7
edge 0 1
)";

Asset::Definition SecondHand =
R"("
id SecondHand
vert 0.0 0.0
vert 0.0 0.85
edge 0 1
)";


} // end namespace Asset
