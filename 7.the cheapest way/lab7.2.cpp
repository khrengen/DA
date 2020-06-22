#include <iostream>
#include <vector>

using namespace std;

long long TripleMin (long long a, long long b, long long c) {
	return min(min(a,b), c);
}


int main() {
	int m,n;
	long long x;
	cin >> m >> n;
	vector<long long> a(m * n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> x;
			a[i * n + j] = x;
		}
	}
	vector<long long> fine (m * n);
	for (int j = 0; j < n; j++) {
		fine[j] = a[j];
	}

	for (int i = 1; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0) {
				fine[i * n] = a[i * n] + min(fine[(i - 1) * n], fine[(i - 1) * n + 1]);
			
			} else if (j == n - 1) {
				fine[i * n + j] = a[i * n + j] + min(fine[(i - 1) * n + j], fine[(i - 1) * n + j - 1]);
			} else {
				fine[i * n + j] = a[i * n + j] + TripleMin(fine[(i - 1) * n + j - 1], fine[(i - 1)* n + j], fine[(i - 1) * n + j + 1]);
			}
			
			
		}
	}

	long long min = fine[(m - 1) * n];
	int pos = 0;
	for (int i = 1; i < n; i++) {
		if (fine[(m - 1) * n + i] < min) {
			min = fine[(m - 1) * n + i];
			pos = i;
		}
	}

	cout << min << '\n';

	vector<int> way;
	way.push_back(pos);
	for (int i = m - 2; i >= 0; i--) {
		if ((pos != 0) && (fine[(i + 1) * n + pos] - a[(i + 1) * n + pos] == fine[i * n + pos - 1])) {
			pos--;
			way.push_back(pos);
		} else if (fine[(i + 1) * n + pos] - a[(i + 1) * n + pos] == fine[i * n + pos]){
			way.push_back(pos);
		} else if ((pos != n - 1) && (fine[(i + 1) * n + pos] - a[(i + 1) * n + pos] == fine[i * n + pos + 1])) {
			pos++;
			way.push_back(pos);
		} 
	}

	for (int i = way.size() - 1; i >= 0; i--) {
		cout << '(' << way.size() - i << "," << way[i] + 1;
		i == 0 ? cout << ")" : cout << ") ";
	}
	cout << '\n';

	return 0;
}