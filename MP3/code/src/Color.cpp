#include <Color.h>

#include <algorithm>
#include <sstream>

namespace RT
{
	void LoadColorFromConfigFile(const std::string& key, const std::string& value, void *pLocation)
	{
		std::stringstream ss(value);

		F32 r, g, b, a;
		ss >> r >> g >> b >> a;

		Color * pColor = ((Color*)pLocation);
		pColor->r = r;
		pColor->g = g;
		pColor->b = b;
		pColor->a = a;
	}

	Color::Color(ColorU8 c)
	{
		r = (F32)c.r / 255.0f;
		g = (F32)c.g / 255.0f;
		b = (F32)c.b / 255.0f;
		a = (F32)c.a / 255.0f;

		Clamp();
	}

	ColorU8 Color::ToColorU8()const
	{
		return ColorU8(
			(U8)(std::max(0.0f, std::min(1.0f, r)) * 255.0f),
			(U8)(std::max(0.0f, std::min(1.0f, g)) * 255.0f),
			(U8)(std::max(0.0f, std::min(1.0f, b)) * 255.0f),
			(U8)(std::max(0.0f, std::min(1.0f, a)) * 255.0f)
		);
	}

	Color Color::operator+(const Color& other)const
	{
		return Color(
			r + other.r,
			g + other.g,
			b + other.b,
			a + other.a
		);
	}

	Color Color::operator*(const Color& other)const
	{
		return Color(
			r * other.r,
			g * other.g,
			b * other.b,
			a * other.a
		);
	}

	Color& Color::operator+=(const Color& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;

		return *this;
	}

	Color Color::operator*(F32 scalar)const
	{
		return Color(
			r * scalar,
			g * scalar,
			b * scalar,
			a * scalar
		);
	}

	Color Color::operator/(F32 d)const
	{
		return Color(
			r / d,
			g / d,
			b / d,
			a / d
		);
	}

	void Color::Clamp()
	{
		r = std::max(0.0f, std::min(1.0f, r));
		g = std::max(0.0f, std::min(1.0f, g));
		b = std::max(0.0f, std::min(1.0f, b));
		a = std::max(0.0f, std::min(1.0f, a));
	}
}