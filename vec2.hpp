//
// vec2.hpp
//
#pragma once

struct vec2 {
	float x;
	float y;

	vec2();
	vec2(float x, float y);
	vec2(const vec2 & other);

	bool operator ==(const vec2 & other);

};

vec2 operator + (const vec2 & v1, const vec2 & v2);
vec2 operator - (const vec2 & v1, const vec2 & v2);