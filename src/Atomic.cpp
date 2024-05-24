#include"Atomic.hpp"
#include<cmath>
#include<iostream>

namespace sha
{
	Atomic::Atomic(value_t p, value_t m, value_t v)
	{
		pos = p;
		mass = m;
		vari = v;
	}

	void Atomic::force(value_t f, const Atomic& b)
	{
		const auto n = pos - b.p();

		value_t s = n;
		value_t t = n + f;
		for(int i = 0; i < 10; i++)
		{
			const auto m = (s + t) / 2;
			const auto L = b.length(n, m);

			if(L > std::abs(f)) t = m;
			else s = m;
		}

		const auto q = (s + t) / 2;
		const auto d = derivate(q);

		pos = b.p() + q - d;
	}

	Atomic::value_t Atomic::length(value_t a, value_t b) const
	{
		auto integ = [&](value_t x) -> value_t
		{
			const float df = derivate(x);
			const float b = 1.0 + df * df;
			const float y = 2.0f / 3.0f * b * std::sqrt(b);
			return y;
		};

		return std::abs(integ(b)) + std::abs(integ(a));
	}

	Atomic::value_t Atomic::dist(value_t x) const
	{
		return mass * std::exp(-x * x / vari);
	}

	Atomic::value_t Atomic::derivate(value_t x) const
	{
		constexpr float eps = 0.001f;

		const float df = (dist(x + eps) - dist(x)) / eps;
		return df;
	}
}
