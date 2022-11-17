#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <complex>
#include <numbers>

using namespace std;

const double PI = 3.141592653589793238463;

complex<double> precision(complex<double> f, int places)
{
	double n = std::pow(10.0f, places);
	return complex<double>((std::round(f.real() * n) / n), (std::round(f.imag() * n) / n));
}

vector<complex<double>> FFT(vector<complex<double>> samples)
{
	if (samples.size() <= 1) return samples;

	const int N = samples.size();
	const int M = samples.size() / 2;

	vector<complex<double>> even;
	vector<complex<double>> odd;

	for (int i = 0; i < M; i++)
	{
		even.push_back(samples[i * 2]);
		odd.push_back(samples[(i * 2) + 1]);
	}

	vector<complex<double>> reorded(N);
	auto re = FFT(even);
	auto ro = FFT(odd);
	
	for (int k = 0; k < M; k++)
	{
		complex<double> cmpExp = polar(1.0, (-2 * PI * k) / N) * ro[k]; //equivalent to (r * (cos(theta) + sin(theta) * 1i)) where (polar(r, theta))

		reorded[k] = precision(re[k] + cmpExp, 3);
		reorded[k + M] = precision(re[k] - cmpExp, 3);
	}

	return reorded;
}

string s;

extern "C" const char* fft(const char* strS,int SamplingRate)
{
	vector<complex<double>> samples;
	stringstream ss(strS);
	vector<string> tokens;
	string temp_str;

	while (getline(ss, temp_str, ','))
	{
		tokens.push_back(temp_str);
	}
	for (int i = 0; i < tokens.size(); i++)
	{
		samples.push_back(stod(tokens[i]));
	}

	auto Interval = SamplingRate / samples.size();

	auto reorded = FFT(samples);

	reorded.erase(reorded.begin() + (reorded.size() / 2), reorded.end());
	for (auto& a : reorded)
	{
		a *= 2;
	}

	s.clear();
	s += "{\n";
	int i = 0;

	for (auto& a : reorded)
	{
		stringstream string_object_name;
		string_object_name << abs(a);

		string str = "\":"; // ":
		string objName = "\"" + string_object_name.str() + "\""; // "objName"
		stringstream sint;
		sint << i;

		s += "\"f" + sint.str() + str + objName + ",\n"; //"fi":"objName\n"

		i+= Interval;
	}
	s.pop_back();
	s.pop_back();
	s += "\n}";

	return s.c_str();
}


int main()
{
	//cout<<fft("0,1,0,-1,0,1,0,-1");

	

	return 0;
}


/*

extern "C" const char* fft(double strVector)
{
	

	auto reorded = FFT(samples);

	reorded.erase(reorded.begin() + (reorded.size() / 2), reorded.end());
	for (auto& a : reorded)
	{
		a *= 2;
	}

	string s = "{\n";
	int i = 0;

	for (auto& a : reorded)
	{
		stringstream string_object_name;
		string_object_name << abs(a);

		string str = "\":"; // ":
		string objName = "\"" + string_object_name.str() + "\""; // "objName"
		stringstream sint;
		sint << i;

		s += "\"f" + sint.str() + str + objName + ",\n"; //"fi":"objName\n"

		i++;
	}
	s.pop_back();
	s.pop_back();
	s += "\n}";

	//cout << s;

	return s.c_str();
}



*/