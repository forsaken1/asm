#include <iostream>

int main() {
	unsigned long long time[1001], time_null[1001];
	int count = 0, a = 0, d = 0;

	for(int i = 1; i <= 1000; i++) {
		int *m = (int*)malloc(sizeof(int) * 1000 * i);

		if(m == NULL)
			break;

		count++;

		//--- Цикл с обращением к памяти ---
		_asm {
			cpuid
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
			cpuid
		}
		time[i] = d;
		time[i] << 32;
		time[i] = a;
		
		//--- Цикл без обращения к памяти ---

		a = 0;
		d = 0;

		_asm {
			cpuid
			mov eax, 0
			mov edx, 0
			rdtsc
			mov a, eax
			mov d, edx
		}

		for(int j = 0; j < 1000 * i; j++) {
			j * j;
		}

		_asm {
			mov eax, 0
			mov edx, 0
			rdtscp
			sub edx, d
			sub eax, a
			mov d, edx
			mov a, eax
			cpuid
		}
		time_null[i] = d;
		time_null[i] << 32;
		time_null[i] = a;
		free(m);
	}

	freopen("output.xls", "w", stdout);

	int s = sizeof(int) * 1000;

	for(int i = 1; i < count; i += 5)
		std::cout << i * s << "\t" << time[i] << "\t" << time_null[i] << std::endl;

	return 0;
}