#include"Curve.hpp"

namespace sha
{
	Curve::Curve(double p, double h, double v)
	{
		pos = p;
		height = h;
		variance = v;
	}

	double Curve::f(double x) const
	{
		const double n = x - pos;
		return height * std::exp(-n * n / variance);
	}

	double Curve::derivate(double x) const
	{
		return (f(x + EPSILON) - f(x)) / EPSILON;
	}

	double Curve::distance(double from, double to) const
	{
		auto integ = [&](double x) -> double
		{
			constexpr double c = 2.0 / 3.0;
			const double dx = derivate(x);
			return c * std::pow(1.0 + dx * dx, 1.5);
		};

		return std::abs(integ(to)) + std::abs(integ(from));
	}

	double Curve::synth_f(double x, const std::vector<Curve>& entries)
	{
		double y = 0;
		for(const auto& e : entries) y += e.f(x);
		return y;
	}

	double Curve::synth_derivate(double x, const std::vector<Curve>& entries)
	{
		double d = 0;
		for(const auto& e : entries) d += e.derivate(x);
		return d;
	}

	double Curve::synth_distance(double from, double to, const std::vector<Curve>& entries)
	{
		auto integ = [&](double x) -> double
		{
			constexpr double c = 2.0 / 3.0;
			const double dx = synth_derivate(x, entries);
			return c * std::pow(1.0 + dx * dx, 1.5);
		};

		return std::abs(integ(to)) + std::abs(integ(from));
	}

	double Curve::move_to(double x, double f, const std::vector<Curve>& entries)
	{
		double s = x;
		double t = x + f;
		for(int i = 0; i < 10; i++)
		{
			const double m = (s + t) / 2;
			const double d = synth_distance(x, m, entries);

			if(d > std::abs(f)) t = m;
			else s = m;
		}

		const double a = synth_derivate((s + t) / 2, entries);

		return (s + t) / 2 - a;
	}

}
