//
// vec2.cpp
//
#include "vec2.hpp"

#include <cmath>
using std::sqrt;

//---------------------------------------------------------------------------------------
vec2::vec2()
	: x(0.0f),
	  y(0.0f)
{

}

//---------------------------------------------------------------------------------------
vec2::vec2 (float x, float y)
	: x(x),
	  y(y)
{

}

//---------------------------------------------------------------------------------------
vec2::vec2(float x)
	: x(x),
	  y(x)
{

}

//---------------------------------------------------------------------------------------
vec2 vec2::operator * (float x) const
{
	vec2 result(*this);
	result.x *= x;
	result.y *= x;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 & vec2::operator += (const vec2 & other)
{
	x += other.x;
	y += other.y;

	return *this;
}

//---------------------------------------------------------------------------------------
bool vec2::operator == (const vec2 & other) const
{
	return (this->x == other.x) && (this->y == other.y);
}

//---------------------------------------------------------------------------------------
vec2 vec2::operator + (const vec2 & other) const
{
	vec2 result(*this);
	result.x += other.x;
	result.y += other.y;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 vec2::operator - (const vec2 & other) const
{
	vec2 result(*this);
	result.x -= other.x;
	result.y -= other.y;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 vec2::operator * (const vec2 & other) const
{
	vec2 result(*this);
	result.x *= other.x;
	result.y *= other.y;

	return result;
}

//---------------------------------------------------------------------------------------
vec2 normalize(const vec2 & v)
{
	float x = v.x;
	float y = v.y;
	float inv_sqrt = 1.0f / sqrt(x*x + y*y);

	return vec2(x * inv_sqrt, y * inv_sqrt);
}

//---------------------------------------------------------------------------------------
float length(const vec2 & v)
{
	float x = v.x;
	float y = v.y;
	return sqrt(x*x + y*y);
}

