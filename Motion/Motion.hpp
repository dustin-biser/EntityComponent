//
// Motion.hpp
//
#pragma once

#include "Core/Component.hpp"
#include "Core/vec2.hpp"


class Motion final : public Component {
public:
	Motion ();

	Motion (
		const GameObject & gameObject
	);

	Motion & operator = (const Motion & other);


	vec2 velocity;
};
