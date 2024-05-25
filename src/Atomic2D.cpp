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

	Curve Atomic2D::cut(Vec2 p, Vec2 d) const
	{
		const Vec2 n = p - pos;
		const Vec2 h = d * d.dot(-n) / (d.lengthSq() + EPSILON);
		const Vec2 v = -n - h;

		//方向
		const double f = h.dot(d) / (h.length() * d.length() + EPSILON);

		const double curve_p = f * h.length();
		const double curve_h = height * std::exp(-v.lengthSq()/variance);
		return Curve(curve_p, curve_h, variance);
	}

	Vec2 Atomic2D::force(Vec2 p, Vec2 f, const std::vector<Atomic2D>& entries)
	{
		std::vector<sha::Curve> curves = {};
		const Vec2 norm = f.normalize();
		for(int i = 0; i < entries.size(); i++)
		{
			curves.emplace_back(entries[i].cut(p, norm));
		}

		const double new_p = sha::Curve::move_to(0, f.length(), curves);
		const Vec2 v = new_p * norm;
		std::cout << "(" << v.x << "," << v.y << ")" << std::endl;

		return new_p * norm;
	}
}
