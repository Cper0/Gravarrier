#include<Siv3D.hpp>
#include"Atomic.hpp"
#include"Const.hpp"

constexpr float r = 3;
constexpr double ALPHA = 5;

sha::Atomic a(320, 10, 1);
sha::Atomic b(100, 10, 1);

double func(double x)
{
	const double ax = x - a.p();
	const double bx = x - b.p();
	return a.dist(ax) + b.dist(bx);
}


void Main()
{
	Window::Resize(640, 400);

	const JSON json = JSON::Load(U"settings.json");

	const float f = json[U"f"].get<float>();



	while(System::Update())
	{
		b.force(1, a);
		if(KeyLeft.pressed())
		{
			a.force(-f, b);
		}
		if(KeyRight.pressed())
		{
			a.force(f, b);
		}

		LineString points;
		for(int i = 1; i < 1000; i++)
		{
			const double x = 640.0 * i / 1000;
			const double y = func(x);
			points << Vec2{x, 200 + y};
		}
		points.draw(2, ColorF{1.0f});

		Circle{a.p(), 200, r}.draw(ColorF{1, 0, 0});
		Circle{b.p(), 200, r}.draw(ColorF{0, 0, 1});
	}
}
