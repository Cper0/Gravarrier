#pragma once

#include<Siv3D.hpp>
#include"Const.hpp"

namespace sha
{
	class Curve
	{
	public:
		Curve(double p, double h, double v);

		double f(double x) const;
		double derivate(double x) const;
		double distance(double from, double to) const;

		double getX() const noexcept { return pos; }
		void setX(double p) noexcept { pos = p; }

		static double synth_f(double x, const std::vector<Curve>& entries);
		static double synth_derivate(double x, const std::vector<Curve>& entries);
		static double synth_distance(double from, double to, const std::vector<Curve>& entries);

		static double move_to(double x, double f, const std::vector<Curve>& entries);

	private:
		double pos;
		double height;
		double variance;
	};
}
