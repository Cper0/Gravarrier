#include"Atomic2D.hpp"

namespace sha
{
	Atomic2D::Atomic2D(const Atomic2D& t)
	{
		pos = t.pos;
		height = t.height;
		variance = t.variance;
	}

	Atomic2D::Atomic2D(Vec2 p, double h, double v)
	{
		pos = p;
		height = h;
		variance = v;
	}

	double Atomic2D::f(Vec2 v) const
	{
		const double x = v.x - pos.x;
		const double y = v.y - pos.y;
		return height * std::exp(-(x*x + y*y) / variance);
	}

	double Atomic2D::synth_f(Vec2 v, const std::vector<Atomic2D>& entries)
	{
		double z = 0;
		for(const auto& e : entries) z += e.f(v);
		return z;
	}

	double Atomic2D::arc_length(Vec2 a, Vec2 b, const std::vector<Atomic2D>& entries)
	{
		constexpr int DIV = 30;

		double area = 0;

		const Vec2 e = b.movedBy(-a).normalize();
		const double k = b.movedBy(-a).length();
		for(int i = 0; i < DIV; i++)
		{
			const Vec2 s = a + e * k * i / DIV;
			const Vec2 t = a + e * k * (i + 1) / DIV;

			const double l = Math::Sqrt2 * k / DIV;
			const double sz = synth_f(s, entries);
			const double tz = synth_f(t, entries);

			area += l * (sz + tz) / 2;
		}

		return area;
	}

	Vec2 Atomic2D::force(Vec2 p, Vec2 f, const std::vector<Atomic2D>& entries)
	{
		Vec2 s = p;
		Vec2 t = p + f;
		for(int i = 0; i < 10; i++)
		{
			const Vec2 m = (s + t) / 2.0;
			const double L = arc_length(p, m, entries);

			if(L > f.length()) t = m;
			else s = m;
		}

		const Vec2 n = (s + t) / 2;
		const double dx = (synth_f(n.movedBy(EPSILON, 0), entries) - synth_f(n, entries)) / EPSILON;
		const double dy = (synth_f(n.movedBy(0, EPSILON), entries) - synth_f(n, entries)) / EPSILON;

		return n - p - Vec2{dx, dy};
	}
}
