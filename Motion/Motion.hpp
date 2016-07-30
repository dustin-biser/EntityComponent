//
// Motion.hpp
//
#pragma once

#include "vec2.hpp"

#include "Core/Component.hpp"


class Motion final : public Component {
public:
	Motion (
		EntityID id,
		GameObject & gameObject
	);

	vec2 velocity;
};
