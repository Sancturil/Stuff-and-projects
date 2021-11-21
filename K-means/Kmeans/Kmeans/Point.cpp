#include "Point.h"
#include <iostream>


void print_point(Point const& point)
{
	std::cout << "{ " << point.mX
		<< ", " << point.mY << "}" << std::endl;
}

Point Point::operator+(Point const& other_point) const
{
	return Point{ mX + other_point.mX, mY + other_point.mY };
}

Point Point::operator/(std::size_t size_vector) const
{
	return Point{ mX/size_vector, mY/size_vector };
}

bool Point::operator==(Point const& other_point) const
{
	return mX == other_point.mX && mY == other_point.mY;
}

bool Point::operator!=(Point const& other_point) const
{
	return !(*this == other_point);
}