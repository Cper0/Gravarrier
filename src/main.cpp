#include<Siv3D.hpp>
#include"Atomic.hpp"
#include"Const.hpp"

constexpr float r = 3;

void Main()
{
	Window::Resize(640, 400);

	const JSON json = JSON::Load(U"settings.json");

	const double af = json[U"a_force"].get<double>();
	const double ah = json[U"a_height"].get<double>();
	const double ad = json[U"a_delta"].get<double>();
	const double ax = json[U"a_x"].get<double>();

	const double bf = json[U"b_force"].get<double>();
	const double bh = json[U"b_height"].get<double>();
	const double bd = json[U"b_delta"].get<double>();
	const double bx = json[U"b_x"].get<double>();

	sha::Atomic a(ax, ah, ad);
	sha::Atomic b(bx, bh, bd);

	auto func = [&](double x) -> double
	{
		const double ax = x - a.p();
		const double bx = x - b.p();
		return a.dist(ax) + b.dist(bx);
	};


	while(System::Update())
	{
		double f = 0;
		if(KeyLeft.pressed()) f = -af;
		if(KeyRight.pressed()) f = af;

		const double m1 = a.force(f, b);
		const double m2 = b.force(bf, a);

		a.move(m1);
		b.move(m2);



		LineString points;
		for(int i = 1; i < 1000; i++)
		{
			const double x = 640.0 * i / 1000;
			const double y = func(x);
			points << Vec2{x, 200 - y};
		}
		points.draw(2, ColorF{1.0f});

		Circle{a.p(), 200 - func(a.p()), r}.draw(ColorF{1, 0, 0});
		Circle{b.p(), 200 - func(b.p()), r}.draw(ColorF{0, 0, 1});
	}
}
