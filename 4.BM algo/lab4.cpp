#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

void BadChar(vector<string> &pat, map<string, int> &bmBc) {
    for (int i = 0; i < pat.size() - 1; ++i) {
        bmBc[pat[i]] = i;
    }
    return;
}

void GoodSuffix(vector<string> &pat, vector<int> &bmGs) {
    int patSize = pat.size();
    int maxZ = 0;
    int maxZindx = 0;
    vector<int> zFunction(patSize, 0);
    for (int i = 1; i < patSize; i++) {
        if (i <= maxZ) {
            zFunction[i] = min(maxZ - i + 1, zFunction[i - maxZindx]);
        }
        while (i + zFunction[i] < patSize && (pat[patSize - 1 - zFunction[i]] == pat[patSize - 1 - (i + zFunction[i])])) {
            zFunction[i]++;
        }
        if (i + zFunction[i] - 1 > maxZ) {
            maxZindx = i;
            maxZ = i + zFunction[i] - 1;
        }
    }
    for (int i = patSize - 1; i > 0; i--) {
        bmGs[patSize - zFunction[i]] = i;
    }
    for (int i = 1; i < patSize; i++) {
        int k = 0;
        if (i + zFunction[i] == patSize) {
            for (; k <= i; k++) {
                if (bmGs[k] == patSize) {
                    bmGs[k] = i;
                }
            }
        }
    }
}

void Low (string &str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
    return;
}

void Read(vector<string> &pat, vector<string> &txt, vector<pair<int,int>> &pairs) {
    string tmp;
    pair<int,int> pr;
    string value;
    getline(cin, tmp, '\n');
    istringstream str_in(tmp);
    while (str_in >> value) {
        Low(value);
        pat.push_back(value);
    }
    int i = 1;
    int index = 0;
    int m;
    int b;
    while (getline(cin, tmp, '\n')) {
        index = 0;
        m = tmp.size();
        for (int j = 1; j <= m;) {
            if ((tmp[j - 1] >= 'a' && tmp[j - 1] <= 'z') || (tmp[j - 1] >= 'A' && tmp[j - 1] <= 'Z')) {
                b = j;
                while (((tmp[j - 1] >= 'a' && tmp[j - 1] <= 'z') || (tmp[j - 1] >= 'A' && tmp[j - 1] <= 'Z')) && j <= m) {
                    j++;
                }
                pr.first = i;
                index++;
                pr.second = index;
                string subtmp;
                subtmp = tmp.substr(b - 1, j - b);
                Low(subtmp);
                txt.push_back(subtmp);
                pairs.push_back(pr);
            }
            j++;
        }
        i++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    vector<string> pat;
    vector<string> txt;
    vector<pair<int,int>> pairs;
    vector<int> strLength;
    map<string, int> bmBc;
    Read(pat, txt, pairs);
    vector<int> bmGs(pat.size() + 1, pat.size());
    BadChar(pat, bmBc);
    GoodSuffix(pat,bmGs);
    vector<int> answer;
    if (pat.size() > txt.size()){
        return 0;
    }
    int j, bound = 0, shift = 0;
    for (int i = 0; i <= txt.size() - pat.size();) {
        for (j = pat.size() - 1; j >= bound; j--) {
            if (pat[j] != txt[i + j]) {
                break;
            }
        }
        if (j < bound) {
            answer.push_back(i);
            bound = pat.size() - bmGs[0];
            j = -1;
        } else {
            bound = 0;
        }
        if (j < bound) {
            shift = bmGs[j + 1];
        } else {
            shift = max(bmGs[j + 1], j - bmBc[txt[ i + j]]);
        }
        i += shift;
    }   
    for (int i = 0; i < answer.size(); ++i) {
        cout << pairs[answer[i]].first << ", " << pairs[answer[i]].second << '\n';
    }
    return 0;
}