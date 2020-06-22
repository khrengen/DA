#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const unsigned long long BASE = 1000000000;
const unsigned long long BASE_COUNT = 9;

void Print(vector<int> &num) {
	cout << num[num.size() - 1];
	for (int i = num.size() - 2; i >= 0; i--) {
		cout << setfill('0') << setw(BASE_COUNT) << num[i];
	}
	cout << '\n';
}

void ZeroClean (vector<int> &vec) {
	while (vec.size() > 1 && vec.back() == 0) {
		vec.pop_back();
	}
}

bool IsEmpty (vector<int> &vec) {
	if (vec.size() == 1 && vec[0] == 0) {
		return true;
	}
	return false;
}

int Compare (vector<int> &a, vector<int> &b) {
	if (a.size() > b.size()){
		return -1;
	} else if (a.size() < b.size()) {
		return 1;
	} else {
		for (int i = a.size() - 1; i >= 0; i--) {
			if (a[i] == b[i]) {
				continue;
			} else if (a[i] > b[i]) {
				return -1;
			} else {
				return 1;
			}
		}
		return 0;
	}
}

void StrToVec (string s, vector<int> &vec) {
	for (int i = s.size(); i > 0; i -= BASE_COUNT) {
		if (i < BASE_COUNT) {
			vec.push_back(atoi(s.substr(0,i).c_str()));
		} else {
			vec.push_back(atoi(s.substr(i - BASE_COUNT, BASE_COUNT).c_str()));
		}
	}
	ZeroClean(vec);
	return;
}

vector<int> Sum (vector<int> a, vector<int> &b) {
	int carry = 0;
	for (int i = 0; i < max(a.size(), b.size()) || carry; i++) {
		if (i == a.size()) {
			a.push_back(0);
		}
		a[i] += carry + (i < b.size() ? b[i] : 0);
		if (a[i] >= BASE) {
			carry = 1;
			a[i] -= BASE;
		} else {
			carry = 0;
		}
	}
	return a;
}

vector<int> Subtrac (vector<int> a, vector<int> &b) {
	int carry = 0;
	for (int i = 0; i < b.size() || carry; i++) {
		a[i] -= carry + (i < b.size() ? b[i] : 0);
		if (a[i] < 0) {
			carry = 1;
			a[i] += BASE;
		} else {
			carry = 0;
		}
	}
	ZeroClean(a);
	return a;
}

vector<int> Mult (vector<int> &a, vector<int> &b) {
	vector<int> res(a.size() + b.size());
	unsigned long long cur;
	unsigned long long carry = 0;
	for (int i = 0; i < a.size(); i++) {
		carry = 0;
		for (int j = 0; j < b.size() || carry; j++) {
			cur = (unsigned long long)res[i + j] + (unsigned long long)a[i] * (j < (int)b.size() ? b[j] : 0) + carry;
			res[i+j] = cur % BASE;
			carry = cur / BASE;
		}
	}
	ZeroClean(res);
	return res;
}

void SimpleMult(vector<int> &a, unsigned long long b) {
	unsigned long long carry = 0;
	unsigned long long cur;
	for (int i = 0; i < a.size() || carry; i++) {
		if (i == a.size()) {
			a.push_back (0);
		}
		cur = carry + (unsigned long long)a[i] * b;
		a[i] = cur % BASE;
		carry = cur / BASE;
	}
	ZeroClean(a);
	return;
}

void SimpleDev(vector<int> &a, int b) {
	unsigned long long carry = 0;
	unsigned long long cur;
	for (int i = a.size() - 1; i >= 0; i--) {
		cur = (unsigned long long)a[i] + carry * BASE;
		a[i] =  cur / b;
		carry = cur % b;
	}
	ZeroClean(a);
	return;
}
bool Odd(vector<int> &vec) {
    return vec[0] & 1;
}

 vector<int> Power(vector<int> a, vector<int> b) {
    if (IsEmpty(a)) {
    	return a;
    }
    if (a.size() == 1 && a[0] == 1) {
    	return a;
    }
    vector<int> result(1,1);
    while (!IsEmpty(b)) {
        if (Odd(b)) {
         	result = Mult(result, a);
        }
        a = Mult(a, a);
        SimpleDev(b, 2);
        //b /= 2;
    }
    return result;
}

vector<int> ShiftRight (vector<int> &vec, int j) {
	if (IsEmpty(vec)) {
		return vec;
	}
	vector<int> shftVec(vec.size() + j, 0);
	copy(vec.begin(), vec.end(), shftVec.begin() + j);
	return shftVec;
}

vector<int> Devis(vector<int> a, vector<int> b){
	int n = b.size();
	int k = a.size();
	int m = k - n;
	vector<int> res(m + 1);
	int d = BASE / (b[n - 1] + 1);
	SimpleMult(a, d);
	a.push_back(0);
	SimpleMult(b, d);
	unsigned long long q = 0, r = 0;
	for (int j = m; j >= 0; j--) {
		q = ((unsigned long long)a[n + j] * BASE + a[n + j - 1]) / b[n - 1];
		r = ((unsigned long long)a[n + j] * BASE + a[n + j - 1]) % b[n - 1];

		while ((q == BASE || (q * b[n - 2]) > (BASE * r + a[j + n - 2])) && r < BASE) {
			q--;
			r += b[n - 1];
		}
		vector<int> shb = ShiftRight(b,j);
		//vector<int> temp = shb;
		SimpleMult(shb,q);
		if (Compare(a, shb) == 1) {
			q--;
			//shb = Subtrac(shb, temp);
			a.push_back(1);
		}
		a = Subtrac(a,shb);
		res[j] = q;

	}
	ZeroClean(res);
	return res;
}
