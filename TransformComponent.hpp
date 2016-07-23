//
// TransformComponent.hpp
//
#pragma once

#include "vec2.hpp"

struct TransformComponent {
	TransformComponent();

	vec2 position;
	vec2 scale;
	float rotationAngle;
};

