#include <math.h>
#include <stdio.h>
#include <iostream>

//
double f(double xi)
{
	return 4.0 / sqrt(4 - xi * xi);
}

double Integrate(int a, int b, int N)
{
	double h = (b - a) / static_cast<double>(N);
	double I = 0, x;
	for (int i = 1; i < N; ++i)
	{
		x = a + i * h;
		I += f(x);
	}
	I += ((f(a) + f(b)) / 2);
	I *= h;
	return I;
}

int main()
{
	int a = 0, b = 1, N = 1000;
	double result = Integrate(a, b, N);
	printf("floats: %.10f  \n", result);
	system("pause");
	return 0;
}