#include <iostream>
#include <string>
#include <math.h>

#define E 0.001

using namespace std;

float u[101][101][16], d_t = 0.01, d_x = 0.1, d_y = 0.1;
float _u[101][101][16];
int n = 20, m = 20, s = 16;

float f_u(float i, float j) {
	return sin(4 * i * d_x) - sin(4 * j * d_y);
}

int main() {
	/*
	function: sin(4x) - sin(4y)
	x from 0 to 2
	y from 0 to 2
	Ox - 20 points
	Oy - 20 points
	delta t = 0.01
	delta x = 0.1
	delta y = 0.1
	*/
	//--- init ---
	for(int i = 0; i < 100; i++)
		for(int j = 0; j < 100; j++)
			for(int k = 0; k < 16; k++) {
				u[i][j][k] = 0;
				_u[i][j][k] = 0;
			}

	//--- starting conditions ---
	for(int i = 1; i < n; i++) //first condition
		for(int j = 1; j < m; j++) {
			u[i][j][1] = f_u(i, j);
			u[i][j][2] = f_u(j, i);

			_u[i][j][1] = f_u(i, j);
			_u[i][j][2] = f_u(j, i);
		}

	for(int j = 1; j < m; j++) //second condition
		for(int k = 1; k < s; k++) {
			u[1][j][k] = 0;
			u[n - 1][j][k] = 0;

			_u[1][j][k] = 0;
			_u[n - 1][j][k] = 0;
		}

	for(int i = 1; i < n; i++)
		for(int k = 1; k < s; k++) {
			u[i][1][k] = 0;
			u[i][m - 1][k] = 0;

			_u[i][1][k] = 0;
			_u[i][m - 1][k] = 0;
		}

	//--- calculating ---
	for(int k = 2; k < s - 1; k++)
		for(int i = 2; i < n - 1; i++)
			for(int j = 2; j < m - 1; j++) {
				u[i][j][k + 1] = (d_t * d_t) * 
				((u[i + 1][j][k] - 2 * u[i][j][k] + u[i - 1][j][k]) / (d_x * d_x) + 
				 (u[i][j + 1][k] - 2 * u[i][j][k] + u[i][j - 1][k]) / (d_y * d_y)) + 
				2 * u[i][j][k] - u[i][j][k - 1];
			}
	
	//--- calculating with SSE ---
	for(int k = 2; k < s - 1; k++)
		for(int i = 2; i < n - 1; i++)
			for(int j = 2; j < m - 1; j++) {
				float a[4] = {d_t, d_x, d_y, 2.0};
				float b[4] = {d_t, d_x, d_y, _u[i][j][k]};
				_asm {
					movups xmm0, a
					movups xmm1, b
					mulps xmm0, xmm1
					movups a, xmm0
				}
				float c[4] = {_u[i + 1][j][k], _u[i][j + 1][k], a[3], 0};
				float d[4] = { a[3], a[3], _u[i][j][k - 1], 0};
				_asm {
					movups xmm0, c
					movups xmm1, d
					subps xmm0, xmm1
					movups c, xmm0
				}
				float e[4] = {c[0], c[1], 0, 0};
				float f[4] = {_u[i - 1][j][k], _u[i][j - 1][k], 0, 0};
				_asm {
					movups xmm0, e
					movups xmm1, f
					addps xmm0, xmm1
					movups e, xmm0
				}
				float g[4] = {e[0], e[1], 0, 0};
				float h[4] = {a[1], a[2], 0, 0};
				_asm {
					movups xmm0, g
					movups xmm1, h
					divps xmm0, xmm1
					movups g, xmm0
				}
				_u[i][j][k + 1] = a[0] * (g[0] + g[1]) + c[2];
			}

	//--- comparing ---
	for(int k = 1; k < s; k++)
		for(int i = 1; i < n; i++)
			for(int j = 1; j < m; j++)
				if(fabs(u[i][j][k] - _u[i][j][k]) > E) {
					cout << "U and _U dont compare" << endl;
					system("PAUSE");
					return 0;
				}

	//--- output ---
	for(int k = 1; k < s; k++) {
		freopen(string("out_" + string(1, k % 10 + '0') + ".txt").c_str(), "w", stdout);
		for(int i = 1; i < n; i++) {
			for(int j = 1; j < m; j++) {
				cout << u[i][j][k] << "\t";
			}
			cout << endl;
		}
	}
	for(int k = 1; k < s; k++) {
		freopen(string("_out_" + string(1, k + '0') + ".txt").c_str(), "w", stdout);
		for(int i = 1; i < n; i++) {
			for(int j = 1; j < m; j++) {
				cout << _u[i][j][k] << "\t";
			}
			cout << endl;
		}
	}
	return 0;
}
