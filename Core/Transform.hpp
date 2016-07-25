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

	Transform operator * (const Transform & other) const;

	vec2 operator * ( const vec2 & vertex );
};
