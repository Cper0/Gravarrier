#pragma once

namespace sha
{
	class Atomic
	{
	public:
		Atomic(float p, float rad, float mass);

		void force(const Atomic& t);

	private:
		float x;
		float r;
		float m;
	};
}
