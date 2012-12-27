#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int u[100][100][16];

int f_u(int i, int j) { //my function: sin(4x) - sin(4y)
	return sin(4 * (double)i) - sin(4 * (double)j);
}

int main() {
	//--- init ---
	for(int i = 0; i < 100; i++)
		for(int j = 0; j < 100; j++)
			for(int k = 0; k < 16; k++)
				u[i][j][k] = 0;

	float d_t = 1, d_x = 1, d_y = 1;
	int n = 64, m = 64, s = 10;

	//--- starting conditions ---
	for(int i = 1; i < n; i++) //first condition
		for(int j = 1; j < m; j++) {
			u[i][j][1] = f_u(i, j);
			u[i][j][2] = f_u(j, i);
		}

	for(int j = 1; j < m; j++) //second condition
		for(int k = 1; k < s; k++) {
			u[1][j][k] = 0;
			u[n - 1][j][k] = 0;
		}

	for(int i = 1; i < n; i++)
		for(int k = 1; k < s; k++) {
			u[i][1][k] = 0;
			u[i][m - 1][k] = 0;
		}

	//--- calculating ---
	for(int i = 2; i < n - 1; i++)
		for(int j = 2; j < m - 1; j++)
			for(int k = 2; k < s - 1; k++) {
				u[i][j][k + 1] = (d_t * d_t) * 
				((u[i + 1][j][k] - 2 * u[i][j][k] + u[i - 1][j][k]) / (d_x * d_x) + 
				 (u[i][j + 1][k] - 2 * u[i][j][k] + u[i][j - 1][k]) / (d_y * d_y)) + 
				2 * u[i][j][k] - u[i][j][k - 1];
			}
			
	//--- output ---
	for(int k = 1; k < s; k++) {
		freopen(string("out_" + string(1, k + '0') + ".txt").c_str(), "w", stdout);
		for(int i = 1; i < n; i++) {
			for(int j = 1; j < m; j++) {
				cout << u[i][j][k] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}
