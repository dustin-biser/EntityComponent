//
// Physics.hpp
//
#pragma once


#include "vec2.hpp"

#include "Core/Component.hpp"


class Physics final : public Component {
public:
	Physics (
		EntityID id,
		GameObject & gameObject
	);



	struct BoundingBox {
		vec2 min;
		vec2 max;
	} boundingBox;

};
