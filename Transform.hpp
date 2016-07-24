//
// Transform.hpp
//
#pragma once

#include "vec2.hpp"

struct Transform {
	Transform();

	vec2 position;
	vec2 scale;
	float rotationAngle;
};

