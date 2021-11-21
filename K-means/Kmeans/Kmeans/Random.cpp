#include "Random.h"

namespace elie {

	Random::Random()
		: m_rd(),
		m_gen(m_rd())
	{}

	int Random::operator()(int lower_bound, int upper_bound)
	{
		std::uniform_int_distribution<> int_distrib(lower_bound, upper_bound);
		return int_distrib(m_gen);
	}

	double Random::operator()(double lower_bound, double upper_bound) 
	{
		std::uniform_real_distribution<double> real_distrib(lower_bound, upper_bound);
		return real_distrib(m_gen);
	}

} // namespace elie