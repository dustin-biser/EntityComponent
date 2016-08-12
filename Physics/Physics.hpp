//
// Physics.hpp
//
#pragma once


#include "vec2.hpp"

#include "Core/Component.hpp"


class Physics final : public Component {
public:
	Physics ();

	Physics (
		const GameObject & gameObject
	);

	Physics & operator = (const Physics & other);


	struct BoundingBox {
		vec2 min;
		vec2 max;
	} boundingBox;

};
