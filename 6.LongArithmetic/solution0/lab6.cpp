#include "longarif.hpp"

int main() {
	string s1, s2;
	char ch;
	vector<int> c;
	while (cin >> s1 >> s2 >> ch) {
		vector<int> a, b;
		StrToVec(s1, a);
		StrToVec(s2, b);
		switch(ch) {
			case '>':
				if (Compare(a,b) == -1) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '<':
				if (Compare(a,b) == 1) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '=':
				if (Compare(a,b) == 0) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '+':
				c = Sum(a,b);
				Print(c);
				break;
			case '-':
				if (Compare(a,b) == 1) {
					cout << "Error\n";
				} else {
					c = Subtrac(a,b);
					Print(c);
				}
				break;
			case '*':
				c = Mult(a,b);
				Print(c);
				break;
			case '/':
				if (IsEmpty(b)) {
					cout << "Error\n";
				} else if (Compare(a,b) == 1) {
					cout << "0\n";
				} else if (b.size() > 1){
					c = Devis(a,b);
					Print(c);
				} else {
					SimpleDev(a,b[0]);
					Print(a);
				}
				break;
			case '^':
				if (IsEmpty(a) && IsEmpty(b)) {
					cout << "Error\n";
				} else {
					c = Power(a,b);
					Print(c);
				}
				break;
			default:
				cout << "Error\n";
				break;
		}
	}
	return 0;
}