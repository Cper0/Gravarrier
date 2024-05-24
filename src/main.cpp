#include<Siv3D.hpp>
#include"Atomic.hpp"

void Main()
{
	Window::Resize(640, 400);

	const JSON json = JSON::Load(U"settings.json");

	constexpr float cam = -100;
	const float f = json[U"f"].get<float>();

	Atomic a(320, 10, 1);
	Atomic b(100, 10, 1);

	while(System::Update())
	{
		Line{0, 200, 640, 200}.draw(ColorF{1.0f});

		Circle{a.p() - cam, 200, r}.draw(ColorF{1, 0, 0});
		Circle{b.p() - cam, 200, r}.draw(ColorF{0, 0, 1});

		if(KeyLeft.pressed())
		{
			a.force(-f, b);
		}
		if(KeyRight.pressed())
		{
			a.force(f, b);
		}
	}
}
