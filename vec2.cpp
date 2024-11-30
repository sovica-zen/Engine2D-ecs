#include "vec2.h"
#include <math.h>

vec2::vec2(): x(0.0), y(0.0) {}
vec2::vec2(float xin, float yin): x(xin), y(yin) {}


vec2 vec2::operator+ (const vec2& rhs) const {
	return (vec2(x + rhs.x, y + rhs.y));
}

vec2 vec2::operator- (const vec2& rhs) const {
	return (vec2(x - rhs.x, y - rhs.y));
}

float vec2::operator* (const vec2& rhs) const {
	return (x*rhs.x + y*rhs.y);
}

vec2 vec2::operator* (const float rhs) const {
	return vec2(x*rhs, y*rhs);
}

vec2 vec2::operator/(const float rhs) const
{
	return vec2(x/rhs,y/rhs);
}

vec2 vec2::operator+= (const vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return (vec2(x,y));
}

vec2 vec2::operator-= (const vec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return (vec2(x, y));
}

vec2 vec2::operator/= (const float rhs) {
	x /= rhs;
	y /= rhs;
	return (vec2(x, y));
}

vec2 vec2::operator*= (const float rhs) {
	x *= rhs;
	y *= rhs;
	return (vec2(x, y));
}

vec2& vec2::add (const vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

float vec2::len() {
	return sqrtf(x*x + y*y);
}

float vec2::dist(const vec2& v) {
	return (*this-v).len();
}


vec2& vec2::normalize()
{
	float l = len();
	if (l < 0.0001) { 
		return *this; 
	}

	x = x / l;
	y = y / l;
	return *this;
}

bool vec2::operator== (const vec2& rhs) const {
	return (x==rhs.x && y==rhs.y);
}

bool vec2::operator!= (const vec2& rhs) const {
	return !(x == rhs.x && y == rhs.y);
}

	

