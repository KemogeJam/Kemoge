//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#include "Easing.h"

#define Pi std::acos(-1.0)

double EaseType::Linear(double f)
{
	return f;
}

double EaseType::Sine(double f)
{
	return 1.0 - std::cos(f * (Pi / 2.0));
}

double EaseType::Quad(double f)
{
	return f * f;
}

double EaseType::Cubic(double f)
{
	return f * f * f;
}

double EaseType::Quart(double f)
{
	return (f * f) * (f * f);
}

double EaseType::Quint(double f)
{
	return (f * f) * (f * f) * f;
}

double EaseType::Expo(double f)
{
	return f == 0.0 ? 0.0 : std::exp2(10.0 * (f - 1.0));
}

double EaseType::Circ(double f)
{
	return 1.0 - std::sqrt(1.0 - f * f);
}

double EaseType::Back(double f)
{
	return f * f * (2.70158 * f - 1.70158);
}

double EaseType::Elastic(double f)
{
	double a = 1.0;
	double p = 0.3;

	if (f == 0) return 0.0;
	else if (f == 1) return 1.0;

	double s;

	if (a < 1.0)
	{
		a = 1.0;

		s = p / 4.0f;
	}
	else s = p / (Pi * 2.0) * std::asin(1.0 / a);

	f -= 1.0;

	return -(a * std::exp2(10.0 * f) * std::sin((f - s) * (Pi * 2.0) / p));
}

double EaseType::Bounce(double f)
{
	f = 1.0 - f;

	if (f < 1 / 2.75)
	{
		return  1.0 - (7.5625 * f * f);
	}
	else if (f < 2 / 2.75)
	{
		f -= 1.5 / 2.75;

		return  1.0 - (7.5625 * f * f + 0.75);
	}
	else if (f < 2.5 / 2.75)
	{
		f -= 2.25 / 2.75;

		return  1.0 - (7.5625 * f * f + 0.9375);
	}
	else
	{
		f -= 2.625 / 2.75;

		return  1.0 - (7.5625 * f * f + 0.984375);
	}
}

double EaseMode::In(double start, double end, std::function<double(double)> easeType, double f)
{
	if (1.0 < f) f = 1.0;

	return start + (end - start) * (easeType)(f);
}

double EaseMode::Out(double start, double end, std::function<double(double)> easeType, double f)
{
	if (1.0 < f) f = 1.0;

	return start + (end - start) * (1.0 - (easeType)(1.0 - f));
}

double EaseMode::InOut(double start, double end, std::function<double(double)> easeType, double f)
{
	if (1.0 < f) f = 1.0;

	return start + (end - start) * ((f < 0.5) ? (easeType)(2.0 * f) * 0.5 : 0.5 + (1.0 - (easeType)(1.0 - (2.0 * f - 1.0))) * 0.5);
}