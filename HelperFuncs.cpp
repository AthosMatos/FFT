#include <cmath>
#include <vector>

using namespace std;

const double pi = 3.14159265358979323846;

float precision(float f, int places)
{
	float n = std::pow(10.0f, places);
	return std::round(f * n) / n;
}

pair<float,float> EulersFormula(int k, int m, int N)
{
	float cosCalc = precision(cos((2 * pi * k * m) / (N / 2)), 3);
	float sinCalc = precision(-sin((2 * pi * k * m) / (N / 2)), 3);

	return pair<float, float>(cosCalc, sinCalc);
}

pair<float, float> EulersFormula2(int k, int N)
{
	float cosCalc = precision(cos((2 * pi * k) / N), 3);
	float sinCalc = precision(-sin((2 * pi * k) / N), 3);
	
	return pair<float, float>(cosCalc, sinCalc);
}