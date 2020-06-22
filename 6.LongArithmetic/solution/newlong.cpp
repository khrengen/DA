#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const int BASE = 1000000000;
const int BASE_COUNT = 9;
const int MAX_DP = 100000;


class TLongInt {
public:
	TLongInt() {
		vec.push_back(0);
	}

	TLongInt(string s) {
		for (int i = s.size(); i > 0; i -= BASE_COUNT) {
			if (i < BASE_COUNT) {
				vec.push_back(atoi(s.substr(0,i).c_str()));
			} else {
				vec.push_back(atoi(s.substr(i - BASE_COUNT, BASE_COUNT).c_str()));
			}
		}
		ZeroClean(vec);
		CheckFull(vec);

	}
	TLongInt(const TLongInt &b) {
		vec = b.vec;
	}

	TLongInt& operator= (const TLongInt &b) {
		vec = b.vec;
		return *this;
	}

	void CheckFull (vector<int> &vec) {
		if (vec.size() > (MAX_DP / BASE_COUNT + 1)) {
			throw("overflow");
		}
	}
	friend bool IsZero (TLongInt &vec) {
		if (vec.size() == 1 && vec[0] == 0) {
			return true;
		}
		return false;
	}

	void ZeroClean (vector<int> &vec) {
		while (vec.size() > 1 && vec.back() == 0) {
			vec.pop_back();
		}
	}

	bool operator== (TLongInt &b) {
		if (size() != b.size()) {
			return false;
		}
		for (int i = 0; i < size(); i++) {
			if (vec[i] != b.vec.size()) {
				return false;
			}
		}
		return true;
	}

	bool operator> (TLongInt &b) {
        if (size() > b.size()) {
            return true;
        } else if (size() < b.size()) {
            return false;
        }
        for (int i = size() - 1; i >= 0; i--) {
        	if (vec[i] == b.vec[i]) {
        		continue;
        	} else if (vec[i] > b.vec[i]) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    bool operator< (TLongInt &b) {
        if (size() < b.size()) {
            return true;
        } else if (size() > b.size()) {
            return false;
        }
        for (int i = size() - 1; i >= 0; i--) {
        	if (vec[i] == b.vec[i]) {
        		continue;
        	} else if (vec[i] < b.vec[i]) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    TLongInt& operator+= (TLongInt &b) {
    	int carry = 0;
		for (int i = 0; i < max(size(), b.size()) || carry; i++) {
			if (i == size()) {
				vec.push_back(0);
			}
			vec[i] += carry + (i < b.size() ? b[i] : 0);
			if (vec[i] >= BASE) {
				carry = 1;
				vec[i] -= BASE;
			} else {
				carry = 0;
			}
		}
	CheckFull(vec);
	return *this;
    }

    TLongInt operator+ (TLongInt &b) {
    	TLongInt res = *this;
    	return res += b;
    }

    TLongInt& operator-= (TLongInt &b) {
    	int carry = 0;
		for (int i = 0; i < b.size() || carry; i++) {
			vec[i] -= carry + (i < b.size() ? b[i] : 0);
			if (vec[i] < 0) {
				carry = 1;
				vec[i] += BASE;
			} else {
				carry = 0;
			}
		}
		ZeroClean(vec);
		return *this;
    }

    TLongInt operator- (TLongInt &b) {
    	TLongInt res = *this;
    	return res -= b;
    }

    TLongInt operator*= (int b) {
    	unsigned long long carry = 0;
		unsigned long long cur;
		for (int i = 0; i < size() || carry; i++) {
			if (i == size()) {
				vec.push_back(0);
			}
			cur = carry + (unsigned long long)vec[i] * b;
			vec[i] = cur % BASE;
			carry = cur / BASE;
		}
		ZeroClean(vec);
		CheckFull(vec);
		return *this;
    }

    TLongInt operator* (int b) {
    	TLongInt res = *this;
    	return res *= b;
    }

    TLongInt operator* (TLongInt &b) {
    	TLongInt res;
    	res.vec.resize(size() + b.size());
    	CheckFull(res.vec);

    	unsigned long long cur;
		unsigned long long carry = 0;
		for (int i = 0; i < size(); i++) {
			carry = 0;
			for (int j = 0; j < b.size() || carry; j++) {
				cur = (unsigned long long)res[i + j] + (unsigned long long)vec[i] * (j < (int)b.size() ? b[j] : 0) + carry;
				res[i+j] = cur % BASE;
				carry = cur / BASE;
			}
		}
		ZeroClean(res.vec);
		return res;
    }

    TLongInt operator/= (int b) {
    	if (b == 1) {
    		return *this;
    	}
    	unsigned long long carry = 0;
		unsigned long long cur;
		for (int i = size() - 1; i >= 0; i--) {
			cur = (unsigned long long)vec[i] + carry * BASE;
			vec[i] =  cur / b;
			carry = cur % b;
		}
		ZeroClean(vec);
		return *this;
    }

    TLongInt operator/ (TLongInt &b) {
    	TLongInt res;
    	if (b.size() == 1) {
    		res = *this;
    		return res /= b[0];
    	}
    	int n = b.size();
		int k = size();
		int m = k - n;
		
		res.vec.resize(m + 1);

		int d = BASE / (b[n - 1] + 1);
		TLongInt u = *this;
		TLongInt v = b;
		u *= d;
		u.vec.push_back(0);
		v *= d;
		TLongInt tmp;

		unsigned long long q = 0, r = 0;
		for (int j = m; j >= 0; j--) {
			q = ((unsigned long long)u[n + j] * BASE + u[n + j - 1]) / v[n - 1];
			r = ((unsigned long long)u[n + j] * BASE + u[n + j - 1]) % v[n - 1];
			

			while ((q == BASE || (q * v[n - 2]) > (BASE * r + u[j + n - 2])) && r < BASE) {
				q--;
				r += v[n - 1];
			}

			tmp = v;
			tmp *= q;
			ShiftRight(tmp, j);

			if (u < tmp) {
				q--;
				u.vec.push_back(1);
			}
			u -= tmp;
			res[j] = q;

		}
		ZeroClean(res.vec);
		return res;
    }


	void ShiftRight (TLongInt &a, int j) {
		if (IsZero(a)) {
			return;
		}
		TLongInt shftVec;
		shftVec.vec.resize(a.size() + j, 0);
		copy(a.vec.begin(), a.vec.end(), shftVec.vec.begin() + j);
		swap(shftVec, a);
	}

		bool Odd(TLongInt &vec) {
    	return vec[0] & 1;
	}


    TLongInt operator^ (TLongInt &b) {

    	if (IsZero(b)) {
    		TLongInt res("1");
    		return res;
    	}

    	if (size() == 1) {	
    		if (vec[0] == 0) {
    			return *this;
    		} else if (vec[0] == 1) {
    			return *this;
    		}
    	}

    	TLongInt result("1");
    	while (!IsZero(b)) {
        	if (Odd(b)) {
         		result = result * *this;
        	}
        	*this = *this * *this;
        	b /= 2;
    	}
    	return result;

    }


	friend istream& operator>> (std::istream &b, TLongInt &in) {
        string s;
        b >> s;
        TLongInt out(s);
        swap(in, out);
        return b;
    }

    friend ostream& operator<< (ostream &b, TLongInt &out) {
        b << out.vec[out.vec.size() - 1];
        for (int i = (int)out.vec.size() - 2; i >= 0; i--) {
            b << setfill('0') << setw(BASE_COUNT) << out.vec[i];
        }
        return b;
    }

    friend void swap(TLongInt &a, TLongInt &b) {
        swap(a.vec, b.vec);
    }

private: 
	vector<int> vec;

	size_t size() {
		return vec.size();
	}

	int& operator[] (int pos) {
		return vec[pos];
	}

};

