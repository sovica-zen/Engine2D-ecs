#pragma once

class vec2 {
private:

public:
	float x;
	float y;

	vec2();
	vec2(float xin, float yin);

	vec2 operator + (const vec2& rhs) const;
	vec2 operator - (const vec2& rhs) const;
	float operator * (const vec2& rhs) const;

	vec2 operator * (const float rhs) const;
	vec2 operator / (const float rhs) const;

	vec2 operator += (const vec2& rhs);
	vec2 operator -= (const vec2& rhs);
	vec2 operator *= (const float rhs);
	vec2 operator /= (const float rhs);
		
	bool operator == (const vec2& rhs) const;
	bool operator!= (const vec2& rhs) const;

	
	vec2& add (const vec2& rhs);
	float dist(const vec2& v);
	float len();
	vec2& normalize();

};

