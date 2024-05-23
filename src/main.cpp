#include<Siv3D.hpp>

constexpr float r = 3;
constexpr float d = 1;
constexpr float h = 10;

float gaussian(float x)
{
	return std::exp(-x * x) * h;
}

float delta(float x)
{
	constexpr float eps = 0.001f;

	const float df = (gaussian(x + eps) - gaussian(x)) / eps;
	return df;
}

float integ(float x)
{
	const float df = delta(x);
	const float b = 1.0 + df * df;
	const float y = 2.0f / 3.0f * b * std::sqrt(b);

	return y;
}

float length(float a, float b)
{
	return std::abs(integ(b)) + std::abs(integ(a));
}

float move_to(float p, float m)
{
	float s = p;
	float t = p + m;
	for(int i = 0; i < 10; i++)
	{
		constexpr float a = 2.f / 3.f;

		const float q = (s + t) / 2;
		const float L = length(p, q);

		//std::cout << q << "," << L << std::endl;

		if(L > std::abs(m))
		{
			t = q;
		}
		else
		{
			s = q;
		}
	}

	return (s + t) / 2;
}

void Main()
{
	Window::Resize(640, 400);

	const JSON json = JSON::Load(U"settings.json");

	constexpr float cam = -100;
	constexpr float q = 0;
	const float f = json[U"f"].get<float>();

	float p = 320;


	while(System::Update())
	{
		Line{0, 200, 640, 200}.draw(ColorF{1.0f});

		Circle{p - cam, 200, r}.draw(ColorF{1, 0, 0});
		Circle{q - cam, 200, r}.draw(ColorF{0, 0, 1});

		float m = 0;
		if(KeyLeft.pressed())
		{
			m += -f;
		}
		if(KeyRight.pressed())
		{
			m += f;
		}

		const float a = move_to(p, m);
		const float d = delta(a);
		p = a - d;
		
	}
}
