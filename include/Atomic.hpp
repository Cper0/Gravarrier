#pragma once

#include<Siv3D.hpp>
#include"Const.hpp"

namespace sha
{
	class Atomic
	{
	public:
		using value_t = double;

		Atomic(value_t p, value_t m, value_t v);

		void force(value_t f, const Atomic& t);

		value_t dist(value_t x) const;
		value_t derivate(value_t x) const;
		value_t length(value_t s, value_t t) const;

		value_t p() const noexcept { return pos; }

		void setP(double p) noexcept { pos = p; }

	private:

		value_t pos;
		value_t mass;
		value_t vari;
	};
}
