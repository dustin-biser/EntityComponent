//
// AssetDefinitions.hpp
//
#pragma once

#include <vector>


// For holding all Asset Definitions accessible during run-time.
class Asset {
public:
	typedef const char * Definition;

	static std::vector<Definition> assetDefinitions;
};
