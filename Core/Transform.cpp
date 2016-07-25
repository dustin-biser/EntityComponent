//
// Transform.cpp
//
#include "Transform.hpp"

#include <cmath>

//---------------------------------------------------------------------------------------
Transform::Transform()
	: position(0.0f, 0.0f),
	  scale(1.0f, 1.0f),
	  rotationAngle(0.0f)
{

}

//---------------------------------------------------------------------------------------
Transform Transform::operator * (
	const Transform & other
) const {
	Transform result;
	result.position = position + other.position;
	result.scale = scale * other.scale;
	result.rotationAngle = rotationAngle + other.rotationAngle;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 Transform::operator * (const vec2 & vertex)
{
	float x = vertex.x;
	float y = vertex.y;

	// Scale
	x = x * scale.x;
	y = y * scale.y;

	// Rotate
	const float angle = rotationAngle;
	if (std::fabs(angle) > 1.0e-6) {
		const float sinAngle = std::sin(angle);
		const float cosAngle = std::cos(angle);
		float x_new = cosAngle * x - sinAngle * y;
		float y_new = sinAngle * x + cosAngle * y;

		x = x_new;
		y = y_new;
	}

	// Translate
	x += position.x;
	y += position.y;

	return vec2{ x, y };

}
