#include <iostream>
#define SIZE 100

using namespace std;

int n;
int v[SIZE], p[SIZE];
bool used[SIZE];

void lex(int pos) {
	if(pos == n) {
        for(int i = 0; i < n; i++)
            cout << v[p[i]] + 1;
        cout << endl;
        return;
    }
    for(int i = 0; i < n; i++) {
        if(!used[i]) {
            used[i] = true;
            p[pos] = i;
            lex(pos + 1);
            p[pos] = 1; 
            used[i] = false;
        }
    }
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++)
		v[i] = i;

	lex(0);
	
	system("PAUSE");
	return 0;
}