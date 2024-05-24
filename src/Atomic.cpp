#include"Atomic.hpp"

namespace sha
{
	Atomic::Atomic(value_t p, value_t m, value_t v)
	{
		pos = p;
		mass = m;
		vari = v;
	}

	void Atomic::force(value_t f, const Atomic& t)
	{
		auto s = pos;
		auto t = pos + f;
		for(int i = 0; i < 10; i++)
		{
			const auto m = (s + t) / 2;
			const auto L = length(pos, m);

			if(L > std::abs(f)) t = m;
			else s = m;
		}

		pos = (s + t) / 2;
	}

	float Atomic::length(float a, float b)
	{
		auto integ = [&](value_t x) -> value_t
		{
			const float df = derivate(x);
			const float b = 1.0 + df * df;
			const float y = 2.0f / 3.0f * b * std::sqrt(b);
		};

		return std::abs(integ(b)) + std::abs(integ(a));
	}

	value_t Atomic::dist(value_t x) const
	{
		return m * std::exp(-x * x / vari);
	}

	value_t Atomic::derivate(value_t x) const
	{
		constexpr float eps = 0.001f;

		const float df = (dist(x + eps) - dist(x)) / eps;
		return df;
	}
}
