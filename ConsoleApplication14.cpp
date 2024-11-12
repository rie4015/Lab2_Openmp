// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <chrono>
#include <iomanip>
#include <windows.h> // For Sleep function
#include <thread>



int par(int numthr, int n)
{
	int sum = 0;
	bool issimple;
	//std::cin » n;
	omp_set_num_threads(numthr);
	auto start = std::chrono::high_resolution_clock::now();

	{
#pragma omp parallel


#pragma omp for schedule(dynamic)
		for (int i = 3; i < n; i++)
		{
			issimple = true;
			for (int j = 2; j < i / 2; j++)
			{
				///std::cout << sum << j;
				///std::cout << i % j;
				if (i % j == 0)
				{
					issimple = false;

				}
			}
			if (issimple == true) {
				sum++;
				/// std::cout << i << std::endl;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	///std::cout << sum;
	int thr = omp_get_num_threads();
	std::cout << std::setw(10) << duration.count() << "ms |";

	return 0;
}




int par1(int numthr, int n)


{
	int sum = 0;
	//std::cin » n;
	auto start = std::chrono::high_resolution_clock::now();
	bool issimple;
	omp_set_num_threads(numthr);
#pragma omp parallel


#pragma omp for schedule(static)
	for (int i = 3; i < n; i++)
	{
		issimple = true;

		for (int j = 2; j < i / 2; j++)
		{
			///std::cout << sum << j;
			///std::cout << i % j;
			if (i % j == 0)
			{
				issimple = false;

			}
		}
		if (issimple == true) {

			sum++;

			/// std::cout << i << std::endl;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	///std::cout << sum;
	int thr = omp_get_num_threads();
	std::cout << std::setw(10) << duration.count() << "ms |";

	return 0;
}




int main()
{
	omp_set_num_threads(5);
#pragma omp parallel
	{
		int thr = omp_get_thread_num();
		std::cout << "Hello World!\n";
	}

	std::cout << "n = 100000" << std::endl;
	int n = 10000;

	std::cout << std::setw(15) << 1 << std::setw(15) << 2 << std::setw(15) << 4 << std::setw(15) << 16 << std::setw(15) << 32 << std::endl;
	std::cout << "static |";
	par1(1, n);
	par1(2, n);
	par1(4, n);
	par1(16, n);
	par1(32, n);

	std::cout << std::endl << "dynamic |";
	par(1, n);
	par(2, n);
	par(4, n);
	par(16, n);
	par(32, n);
	std::cout << std::endl<< "n = 500000" << std::endl;
	n = 10000;

	std::cout << std::setw(15) << 1 << std::setw(15) << 2 << std::setw(15) << 4 << std::setw(15) << 16 << std::setw(15) << 32 << std::endl;
	std::cout << "static |";
	par1(1, n);
	par1(2, n);
	par1(4, n);
	par1(16, n);
	par1(32, n);

	std::cout << std::endl << "dynamic |";
	par(1, n);
	par(2, n);
	par(4, n);
	par(16, n);
	par(32, n);
	std::cout << std::endl;


	int numthr;
	const int N = 1000;
	int m = 400;
	int a[N];
	bool f = false;
	for (int i = 0; i < N; i++) {
		a[i] = i;
	}
	std::cin >> numthr;
	omp_set_num_threads(numthr);
	int* counter = new int[numthr]();
#pragma omp parallel
	{

		int count = 0;

#pragma omp for schedule(dynamic)
		for (int i = 0; i < N; i++) {
			count++;
			int thread = omp_get_thread_num();
			counter[thread] = count;
			//std::cout << thread << " : " << count << "  i:   " << i << std::endl;
			if (f == true)
			{

				std::cout << "Thread: " << thread << " STOP " << std::endl;
				
				std::this_thread::sleep_for(std::chrono::seconds(1000));

				
			}
			else if (a[i] == m) {
				f = true;
				std::cout << "M is " << a[i] << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(3));
				std::cout << "Thread: " << thread << " iterations: " << count << std::endl;
				for (int j = 0; j < numthr; j++) {
					std::cout << "Thread: " << j << " iterations: " << counter[thread] << std::endl;
				}
				std::this_thread::sleep_for(std::chrono::seconds(1000));

				
			}


		}

	}



	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
// 1. В окне обозревателя решений можно добавлять файлы и управлять ими.
// 2. В окне Team Explorer можно подключиться к системе управления версиями.
// 3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
// 4. В окне "Список ошибок" можно просматривать ошибки.
// 5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
// 6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.