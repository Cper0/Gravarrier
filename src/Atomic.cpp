#include"Atomic.hpp"

namespace sha
{
	double slope(double x, const Atomic& a, const Atomic& b)
	{
		const double ax = x - a.p();
		const double bx = x - b.p();
		return a.derivate(ax) + b.derivate(bx);
	}
	
	double arc_length(double s, double t, const Atomic& a, const Atomic& b)
	{
		auto integ = [&](double x)
		{
			const double df = slope(x, a, b);
			const double b = 1.0 + df * df;
			const double y = 2.0f / 3.0f * b * std::sqrt(b);
			return y;
		};

		return std::abs(integ(t)) + std::abs(integ(s));
	}

	Atomic::Atomic(value_t p, value_t m, value_t v)
	{
		pos = p;
		mass = m;
		vari = v;
	}

	double Atomic::force(value_t f, const Atomic& b)
	{
		value_t s = pos;
		value_t t = pos + f;
		for(int i = 0; i < 10; i++)
		{
			const auto m = (s + t) / 2;
			const auto L = arc_length(pos, m, *this, b);

			if(L > std::abs(f)) t = m;
			else s = m;
		}

		const auto q = (s + t) / 2;
		const auto d = slope(q, *this, b);

		return q - pos - d;
	}

	Atomic::value_t Atomic::dist(value_t x) const
	{
		return mass * std::exp(-x * x / vari);
	}

	Atomic::value_t Atomic::derivate(value_t x) const
	{
		const float df = (dist(x + EPSILON) - dist(x)) / EPSILON;
		return df;
	}
}
