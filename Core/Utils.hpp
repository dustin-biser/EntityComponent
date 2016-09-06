//
// Utils.hpp
//
#pragma once

#include <cassert>
#include <cstdlib>


#if defined(_DEBUG)
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif


// Returns a random float in the range [0,1].
__forceinline
float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
