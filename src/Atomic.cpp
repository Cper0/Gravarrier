#include"Atomic.hpp"

namespace sha
{
	Atomic::Atomic(float p, float rad, float mass)
	{
		x = p;
		r = rad;
		m = mass;
	}

	void Atomic::force(float f, const Atomic& t)
	{
		const float d = r / 8;

		

	}
}
