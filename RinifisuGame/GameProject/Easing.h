//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#pragma once
#include <math.h>
#include <functional>

namespace EaseType
{
	double Linear(double f);
	double Sine(double f);
	double Quad(double f);
	double Cubic(double f);
	double Quart(double f);
	double Quint(double f);
	double Expo(double f);
	double Circ(double f);
	double Back(double f);
	double Elastic(double f);
	double Bounce(double f);
}

namespace EaseMode
{
	double In(double start, double end, std::function<double(double)> easeType, double f);
	double Out(double start, double end, std::function<double(double)> easeType, double f);
	double InOut(double start, double end, std::function<double(double)> easeType, double f);
}