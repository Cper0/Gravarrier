#pragma once

#include<Siv3D.hpp>
#include"Curve.hpp"

namespace sha
{
	class Atomic
	{
	public:
		Atomic(double p, double m, double v);

		double force(double f, const Atomic& t);

		//void update();

	private:
		Curve curve;
	};
}
