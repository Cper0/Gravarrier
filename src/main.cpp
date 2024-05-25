#include<Siv3D.hpp>
#include"Atomic2D.hpp"
#include"Const.hpp"
#include"Curve.hpp"

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

	Vec2 a = {ax, 200};
	Vec2 b = {bx, 200};

	std::vector<sha::Atomic2D> atomic = {
		sha::Atomic2D(a, ah, ad),
		sha::Atomic2D(b, bh, bd)
	};
	

	while(System::Update())
	{
		Vec2 f = {1, 0};
		if(KeyLeft.pressed()) f.moveBy(-af, 0);
		if(KeyRight.pressed()) f.moveBy(af, 0);
		if(KeyUp.pressed()) f.moveBy(0, -af);
		if(KeyDown.pressed()) f.moveBy(0, af);

		const Vec2 m1 = sha::Atomic2D::force(a, f, atomic);

		a.moveBy(m1);
		atomic[0].moveBy(m1);

		Circle{atomic[0].p().x, atomic[0].p().y, r}.draw(ColorF{1, 0, 0});
		Circle{atomic[1].p().x, atomic[1].p().y, r}.draw(ColorF{0, 0, 1});
	}
}
