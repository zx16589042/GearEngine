#include "Geometry.h"

Point::Point(void)
{
	set(0.0f, 0.0f);
}

Point::Point( float xx, float yy )
{
	set(xx, yy);
}

Point::Point( const Point& other )
{
	set(other);
}

void Point::set( float xx, float yy )
{
	this->x = xx;
	this->y = yy;
}

void Point::set( const Point& other )
{
	this->x = other.x;
	this->y = other.y;
}

bool Point::equals( const Point& target ) const
{
	return this->x == target.x && this->y == target.y;
}
const Point Point::ZERO = Point(0, 0);


Size::Size(void)
{
	setSize(0.0f, 0.0f);
}

Size::Size( float w, float h )
{
	setSize(w, h);
}

Size::Size( const Size& other )
{
	setSize(other.width, other.height);
}

Size& Size::operator=( const Size& other )
{
	setSize(other.width, other.height);
	return *this;
}

Size Size::operator+( const Size& right ) const
{
	return Size(this->width + right.width, this->height + right.height);
}

Size Size::operator-( const Size& right ) const
{
	return Size(this->width - right.width, this->height - right.height);
}

Size Size::operator*( float a ) const
{
	return Size(this->width * a, this->height * a);
}

Size Size::operator/( float a ) const
{
	return Size(this->width / a, this->height / a);
}

void Size::setSize( float w, float h )
{
	this->width = w;
	this->height = h;
}

bool Size::equals( const Size& target ) const
{
	return this->width == target.width && this->height == target.height;
}

const Size Size::ZERO = Size(0, 0);


Rect::Rect( float x, float y, float width, float height )
{
	setRect(x, y, width, height);
}

Rect::Rect( const Rect& other )
{
	setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

Rect& Rect::operator=( const Rect& other )
{
	setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
	return *this;
}

void Rect::setRect( float x, float y, float width, float height )
{
	origin.x = x;
	origin.y = y;

	size.width = width;
	size.height = height;
}

float Rect::getMinX() const
{
	return origin.x;
}

float Rect::getMidX() const
{
	return origin.x + size.width / 2;
}

float Rect::getMaxX() const
{
	return origin.x + size.width;
}

float Rect::getMinY() const
{
	return origin.y;
}

float Rect::getMidY() const
{
	return origin.y + size.height / 2;
}

float Rect::getMaxY() const
{
	return origin.y + size.height;
}

bool Rect::equals( const Rect& rect ) const
{
	return origin.equals(rect.origin) && size.equals(rect.size);
}

bool Rect::containsPoint( const Point& point ) const
{
	return (point.x >= getMinX() && point.x <= getMaxX()
		 && point.y >= getMinY() && point.y <= getMaxY());
}

bool Rect::intersectsRect( const Rect& rect ) const
{
	return !(	 getMaxX() < rect.getMinX() ||
			rect.getMaxX() <      getMinX() ||
				 getMaxY() < rect.getMinY() ||
			rect.getMaxY() <      getMinY());
}

Rect Rect::unionWithRect( const Rect & rect ) const
{
	float thisLeftX = origin.x;
	float thisRightX = origin.x + size.width;
	float thisTopY = origin.y + size.height;
	float thisBottomY = origin.y;

	if (thisRightX < thisLeftX)
	{
		std::swap(thisRightX, thisLeftX);   // This rect has negative width
	}

	if (thisTopY < thisBottomY)
	{
		std::swap(thisTopY, thisBottomY);   // This rect has negative height
	}

	float otherLeftX = rect.origin.x;
	float otherRightX = rect.origin.x + rect.size.width;
	float otherTopY = rect.origin.y + rect.size.height;
	float otherBottomY = rect.origin.y;

	if (otherRightX < otherLeftX)
	{
		std::swap(otherRightX, otherLeftX);   // Other rect has negative width
	}

	if (otherTopY < otherBottomY)
	{
		std::swap(otherTopY, otherBottomY);   // Other rect has negative height
	}

	float combinedLeftX = std::min(thisLeftX, otherLeftX);
	float combinedRightX = std::max(thisRightX, otherRightX);
	float combinedTopY = std::max(thisTopY, otherTopY);
	float combinedBottomY = std::min(thisBottomY, otherBottomY);

	return Rect(combinedLeftX, combinedBottomY, combinedRightX - combinedLeftX, combinedTopY - combinedBottomY);
}

void Rect::merge( const Rect& rect )
{
	float top1    = getMaxY();
	float left1   = getMinX();
	float right1  = getMaxX();
	float bottom1 = getMinY();

	float top2    = rect.getMaxY();
	float left2   = rect.getMinX();
	float right2  = rect.getMaxX();
	float bottom2 = rect.getMinY();
	origin.x = std::min(left1, left2);
	origin.y = std::min(bottom1, bottom2);
	size.width = std::max(right1, right2) - origin.x;
	size.height = std::max(top1, top2) - origin.y;
}

const Rect Rect::ZERO = Rect(0, 0, 0, 0);
