#pragma once
#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

namespace elie {

class Random
{
public:
	Random();

	int operator()(int lower_bound, int upper_bound);
	double operator()(double lower_bound, double upper_bound);

private:
	std::random_device m_rd;
	std::mt19937 m_gen;

};

} // namespace elie

#endif /* RANDOM_H_ */