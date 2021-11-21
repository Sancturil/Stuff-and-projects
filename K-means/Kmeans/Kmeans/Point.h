#pragma once
#ifndef POINT_H_
#define POINT_H_

#include <cstddef> // std::size_t

struct Point
{
	double mX;
	double mY;

	Point operator+(Point const& other_point) const;
	Point operator/(std::size_t size_vector) const;
	bool operator==(Point const& other_point) const;
	bool operator!=(Point const& other_point) const;

	friend void print_point(Point const& point);

};

#endif /* POINT_H_ */
