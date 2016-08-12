//
// Transform.hpp
//
#pragma once

#include <vector>

#include "Core/EntityID.hpp"
#include "Core/Component.hpp"
#include "Core/vec2.hpp"


// Forward Declare.
class GameObject;


class Transform final : public Component {
public:
	Transform();

	Transform ( 
		const GameObject & gameObject
	);

	void setParent (Transform & parent);

	Transform * getParent() const;

	Transform * childAtIndex (size_t index) const;

	void addChild(Transform & child);

	Transform operator * (const Transform & other) const;

	vec2 operator * (const vec2 & vertex) const;

	// Copies other's Transform fields, and clones the child Transforms
	// of other.
	Transform & operator = (const Transform & other);


	vec2 position;
	vec2 scale;
	float rotationAngle;


private:
	friend class RenderingSystemImpl;
	
	EntityID m_parentId;
	std::vector<EntityID> m_childList;
};
