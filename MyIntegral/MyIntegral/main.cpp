#include <math.h>
#include <stdio.h>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <iostream>
#include <chrono>

//Функция f() - подинтегральная функция
//xi - входной параметр (точка, в которой считается подинтегральная функция)
//функция возвращает значение подинтегральной функции в точке
double f(double xi)
{
	return 4.0 / sqrt(4 - xi * xi);
}

//Функция Integrate() - функция, в которой происходит интегрирование методом трапеции
//a, b - пределы интегрирования
//N - количество отрезков интегрирования
//функция возвращает знчение интеграла
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

//Функция MeanTime() - функция замера времени. Выводит время на экран. Время расчитывается как среднее (запускается программа 10000 раз и берется среднее).
//a, b - пределы интегрирования
//N - количество отрезков интегрирования
//функция возвращает знчение интеграла
void MeanTime(int a, int b, int N)
{
	double fullTime = 0;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	for (int i = 0; i < 10000; ++i)
	{
		start = std::chrono::system_clock::now();
		double result = Integrate(a, b, N);
		end = std::chrono::system_clock::now();
		fullTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}
	std::cout << "Time: " << fullTime / 10000 << " microseconds\n";
}

int main()
{
	int a = 0, b = 1, N = 1000000;
	double result = Integrate(a, b, N);
	MeanTime(a, b, N);
	printf("Result: %.10f\n", result);
	system("pause");
	return 0;
}