//
// Utils.hpp
//
#pragma once

#include <cassert>


#if defined(_DEBUG)
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif

