#pragma once

#include<Siv3D.hpp>
#include"Const.hpp"
#include"Curve.hpp"

namespace sha
{
	class Atomic2D
	{
	public:
		Atomic2D(const Atomic2D& t);
		Atomic2D(Vec2 p, double h, double v);

		Curve cut(Vec2 p, Vec2 d) const;

		void moveBy(Vec2 f) noexcept { pos += f; }

		Vec2 p() const noexcept { return pos; }

		static Vec2 force(Vec2 p, Vec2 f, const std::vector<Atomic2D>& t);

	private:
		Vec2 pos;
		double height;
		double variance;
	};
}
