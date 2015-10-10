#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <algorithm>

class Point
{
public:
	float x;
	float y;
public:
	Point();
	Point(float xx, float yy);
	Point(const Point& other);

	void set(float xx, float yy);
	void set(const Point& other);

	bool equals(const Point& target) const;

	static const Point ZERO;
};


class Size
{
public:
	float width;
	float height;
public:
	Size();
	Size(float w, float h);
	Size(const Size& other);

	Size& operator= (const Size& other);
	Size operator+(const Size& right) const;
	Size operator-(const Size& right) const;
	Size operator*(float a) const;
	Size operator/(float a) const;

	void setSize(float w, float h);

	bool equals(const Size& target) const;

	static const Size ZERO;
};


class Rect
{
public:
	Point origin;
	Size size;
public:
	Rect();

	Rect(float x, float y, float width, float height);

	Rect(const Rect& other);

	Rect& operator= (const Rect& other);

	void setRect(float x, float y, float width, float height);

	float getMinX() const;

	float getMidX() const;

	float getMaxX() const;

	float getMinY() const;

	float getMidY() const;

	float getMaxY() const;

	bool equals(const Rect& rect) const;

	bool containsPoint(const Point& point) const;

	bool intersectsRect(const Rect& rect) const;

	Rect unionWithRect(const Rect & rect) const;

	void merge(const Rect& rect);

	static const Rect ZERO;
};

#endif