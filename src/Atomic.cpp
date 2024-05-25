#include"Atomic.hpp"

namespace sha
{
	Atomic::Atomic(double p, double m, double v) : curve(p, m, v)
	{
	}

	double Atomic::force(double f, const Atomic& b)
	{
		return 0;
	}
}
