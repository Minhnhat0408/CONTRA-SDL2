#pragma once

#include <iostream>
#include<math.h>
using namespace std;

struct Vector2f
{
	double x, y;
	Vector2f():x(0.f), y(0.f) {};
	Vector2f(double p_x, double p_y)
	:x(p_x), y(p_y) {}

	void prdouble() const
	{
		std::cout << x << ", " << y << std::endl;
	}

	double length()
	{
		return sqrt(x*x + y*y);
	}

	Vector2f operator+(Vector2f p_v)
	{	
		Vector2f ans(p_v.x + x,p_v.y+y);
		return ans;
	}
	Vector2f operator-(Vector2f p_v)
	{	
		Vector2f ans(x - p_v.x,y-p_v.y);
		return ans;
	}
	void operator*(Vector2f p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
	}
	void operator/=(Vector2f p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
	}

	// Scalar
	Vector2f operator+(double p_s)
	{	
		Vector2f ans(x+p_s,y+p_s);
		return  ans;
	}
	void operator-=(double p_s)
	{
		x -= p_s;
		y -= p_s;
	}
	void operator*=(double p_s)
	{
		x *= p_s;
		y *= p_s;
	}
	void operator/=(double p_s)
	{
		x /= p_s;
		y /= p_s;
	}

	bool operator==(Vector2f p_v)
	{
		if (x == p_v.x && y == p_v.y)
			return true;
		return false;
	}
};