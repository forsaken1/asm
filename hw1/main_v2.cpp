#include <iostream>
#include <string>

using namespace std;

int letter[26];

int GetLengthUniqueString(string s) {
	int r = 0, l = 0, R = r, L = l;

	while(r < s.length()) {
		if(letter[s[r] - 97]) {
			letter[s[l] - 97] = 0;
			l++;
			continue;
		}
		letter[s[r] - 'a'] = 1;
		if(R - L < r - l) {
			R = r;
			L = l;
		}
		r++;
	}
	return R - L + 1;
}

int main() {
	string s;
	
	cout << "Enter string" << endl;
	cin >> s;
	cout << GetLengthUniqueString(s) << endl;

	system("PAUSE");

	return 0;
}