#include <math.h>
#include <stdio.h>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <iostream>

//������� f() - ��������������� �������
//xi - ������� �������� (�����, � ������� ��������� ��������������� �������)
//������� ���������� �������� ��������������� ������� � �����
double f(double xi)
{
	return 4.0 / sqrt(4 - xi * xi);
}

//������� Integrate() - �������, � ������� ���������� �������������� ������� ��������
//a, b - ������� ��������������
//N - ���������� �������� ��������������
//������� ���������� ������� ���������
double Integrate(int a, int b, int N)
{
	double h = (b - a) / static_cast<double>(N), I = 0;
	cilk::reducer_opadd<double> sum(0.0);
	cilk_for (int i = 1; i < N; ++i)
	{
		double x = a + i * h;
		sum += f(x);
	}
	I = sum.get_value() + ((f(a) + f(b)) / 2);
	I *= h;
	return I;
}

int main()
{
	int a = 0, b = 1, N = 1000000;
	double result = Integrate(a, b, N);
	printf("Result: %.10f\n", result);
	system("pause");
	return 0;
}