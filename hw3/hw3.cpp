#include <iostream>

int main() {
	int time[1001], _time[1001], time_null[1001], _time_null[1001], count = 0, a = 0, d = 0;

	for(int i = 1; i <= 1000; i++) {
		int *m = (int*)malloc(sizeof(int) * 1000 * i);

		if(m == NULL)
			break;

		count++;

		//Обращение к памяти
		_asm {
			mov eax, 0
			mov edx, 0
			rdtsc
			mov a, eax
			mov d, edx
		}

		for(int j = 0; j < 1000 * i; j++) {
			m[j] = j * j;
		}

		_asm {
			mov eax, 0
			mov edx, 0
			rdtscp
			sub edx, d
			sub eax, a
			mov d, edx
			mov a, eax
		}
		time[i] = a;
		_time[i] = d;

		a = 0;
		d = 0;
		//Пустой цикл
		_asm {
			mov eax, 0
			mov edx, 0
			rdtsc
			mov a, eax
			mov d, edx
		}

		for(int j = 0; j < 1000 * i; j++) {}

		_asm {
			mov eax, 0
			mov edx, 0
			rdtscp
			sub edx, d
			sub eax, a
			mov d, edx
			mov a, eax
		}
		time_null[i] = a;
		_time_null[i] = d;
		free(m);
	}

	freopen("output.txt", "w", stdout);

	for(int i = 1; i < count; i += 5)
		std::cout << i << " " << _time[i] << time[i] << std::endl;

	freopen("output_null.txt", "w", stdout);

	for(int i = 1; i < count; i += 5)
		std::cout << i << " " << _time_null[i] << time_null[i] << std::endl;

	return 0;
}