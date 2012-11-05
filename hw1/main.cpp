#include <iostream>
#include <string>

using namespace std;

int UniqueMaximalSubstring(string str) {
	int l = 0, r = 0, L = l, R = r;

	while(r < str.size()) {
		for(int i = l; i < r; i++) {
			if(str[r] == str[i]) {
				l = i + 1;
				r = l;
				break;
			}
		}
		if(R - L < r - l) {
			R = r;
			L = l;
		}
		r++;
	}
	return R - L + 1;
}

void test(bool a) {
	if(a) cout << "Test successful" << endl;
	else  cout << "Test error" << endl;
}

int main() {
	test(UniqueMaximalSubstring("a") == 1);
	test(UniqueMaximalSubstring("worldwideweb") == 6);
	test(UniqueMaximalSubstring("internet") == 5);
	test(UniqueMaximalSubstring("perlprogramminglanguage") == 6);
	test(UniqueMaximalSubstring("personalhomepage") == 9);
	test(UniqueMaximalSubstring("onebadword") == 8);
	test(UniqueMaximalSubstring("aaaaaabbbbbcccdeeeeeeeeee") == 3);
	test(UniqueMaximalSubstring("qwertyuioplkjhgfdsazxcvbnm") == 26);
	test(UniqueMaximalSubstring("cab") == 3);
	test(UniqueMaximalSubstring("strings") == 6);

	system("PAUSE");
	return 0;
}