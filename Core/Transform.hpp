//
// Transform.hpp
//
#pragma once

#include "vec2.hpp"

#include "Core/Component.hpp"

class Transform : public Component {
	Transform();

	vec2 position;
	vec2 scale;
	float rotationAngle;

	Transform operator * (const Transform & other) const;

	vec2 operator * ( const vec2 & vertex );
};
