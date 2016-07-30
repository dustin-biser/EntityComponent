//
// Transform.hpp
//
#pragma once

#include "vec2.hpp"

#include "Core/Component.hpp"

class Transform final : public Component {
public:
	Transform();

	Transform ( 
		EntityID id,
		GameObject & gameObject
	);

	Transform operator * (const Transform & other) const;

	vec2 operator * ( const vec2 & vertex );


	vec2 position;
	vec2 scale;
	float rotationAngle;
};
