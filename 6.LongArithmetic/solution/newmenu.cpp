#include "newlong.cpp"

int main() {
	char ch;
	TLongInt a, b, c;
	while (cin >> a >> b >> ch) {
		switch(ch) {
			case '>':
				if (a > b) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '<':
				if (a < b) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '=':
				if (a == b) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
				break;
			case '+':
				c = a + b;
				cout << c << '\n';
				break;
			case '-':
				if (a < b) {
					cout << "Error\n";
				} else {
					c = a - b;
					cout << c << '\n';
				}
				break;
			case '*':
				c = a * b;
				cout << c << '\n';
				break;
			case '/':
				if (IsZero(b)) {
					cout << "Error\n";
				} else if (a < b) {
					cout << "0\n";
				} else {
					c = a / b;
					cout << c << '\n';
				}
				break;
			case '^':
				if (IsZero(a) && IsZero(b)) {
					cout << "Error\n";
				} else {
					c = a ^ b;
					cout << c << '\n';
				}
				break;
			default:
				cout << "Error\n";
				break;
		}
	}
	return 0;
}