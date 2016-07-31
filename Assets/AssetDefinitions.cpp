//
// AssetDefinitions.cpp
//
#include "AssetDefinitions.hpp"


std::vector<Asset::Definition> Asset::assetDefinitions = {

R"(
id Cannon
vert -0.5 0.0
vert 0.5 0.0
vert 0.0 1.0
edge 0 2
edge 0 1
edge 1 2
)",

R"(
id Projectile
vert 0.0 -0.2
vert 0.0 0.2
edge 0 1
)",

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
)",

R"(
id HourHand
vert 0.0 0.0
vert 0.0 0.45
edge 0 1
)",


R"(
id MinuteHand
vert 0.0 0.0
vert 0.0 0.7
edge 0 1
)",

R"("
id SecondHand
vert 0.0 0.0
vert 0.0 0.85
edge 0 1
)"

}; // end assetDefinitions
