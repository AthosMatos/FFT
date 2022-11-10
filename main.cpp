#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;
const double pi = 3.14159265358979323846;

float precision(float f, int places)
{
	float n = std::pow(10.0f, places);
	return std::round(f * n) / n;
}
pair<float, float> EulersFormula(int k, int m, int N)
{
	float cosCalc = precision(cos((-2 * pi * k * m) / (N / 2)), 3);
	float sinCalc = precision(sin((-2 * pi * k * m) / (N / 2)), 3);

	return pair<float, float>(cosCalc, sinCalc);
}
pair<float, float> EulersFormula(int k, int N)
{
	float cosCalc = precision(cos((-2 * pi * k) / N), 3);
	float sinCalc = precision(sin((-2 * pi * k) / N), 3);

	return pair<float, float>(cosCalc, sinCalc);
}
float GetFEven(int k,int N, vector<int> Samples)
{
	float evenCalc = 0;

	for (int m = 0; m <= ((N / 2) - 1); m++)
	{
		const auto EFR = EulersFormula(k, m, N);
		evenCalc += Samples[2 * m] * (EFR.first + EFR.second);
	}

	return evenCalc;
}
float GetFOdd(int k, int N, vector<int> Samples)
{
	float oddCalc = 0;

	for (int m = 0; m <= ((N / 2) - 1); m++)
	{
		const auto EFR = EulersFormula(k, m, N);
		oddCalc += Samples[2 * m + 1] * (EFR.first + EFR.second);
	}
	const auto EFR = EulersFormula(k, N);
	oddCalc *= (EFR.first + EFR.second);

	return oddCalc;
}

struct EO
{
	float even;
	float odd;
};

vector<EO> freqs;

float FFT(int N, vector<int> Samples)
{
	for (int k = 0; k < N / 2; k++)
	{
		auto F_even = GetFEven(k, N, Samples);
		auto F_odd = GetFOdd(k, N, Samples);

		EO eo;
		eo.even = F_even;
		eo.odd = F_odd;

		freqs.push_back(eo);

		//FFT(N, Samples);
		//cout << "F" << k << " " << F_even + F_odd << endl;
	}



	return 0;
}



int main()
{
	FFT(4, vector<int>{0, 1, 0, -1 });

	return 0;
}