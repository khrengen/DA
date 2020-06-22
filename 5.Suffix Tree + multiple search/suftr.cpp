#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class SufTree {
public:
	SufTree(string &str) {
		root = new SufNode();
		s = str;
		end = 0;
		activeEdge = -1; 
		activeLength = 0;
		remainingSuffixCount = 0;
		active = root;

		for (int i = 0; i < s.size(); i++) {
			Extensions(i);
		}
	}

	~SufTree() {
		Clean(root);
	}

	void Build() {
		GetIndex(root, 0);
	}

	vector<int> TreeSearch(string &str) {
		return Search(root, str);
	}

private:
	struct SufNode {
		map<char,SufNode*> children;
		int left;
		int *right;
		SufNode *sufLink;
		int sufIndex;

		SufNode():
                left(-2), sufIndex(-1)
                {
                }

        SufNode(int l, int* r):
                left(l), right(r), /*sufLink(root),*/ sufIndex(-1)
                {
                }
	};

	bool IsLeaf(SufNode* n) {
		if(n->sufIndex == -1) {
			return false;
		} else {
			return true;
		}
	}

	int edgeLength(SufNode *n) { 
    	return *(n->right) - (n->left) + 1; 
	} 

	
	int SkipDown(SufNode *currNode) { 
    	if (activeLength >= edgeLength(currNode)) { 
        	activeEdge += edgeLength(currNode); 
        	activeLength -= edgeLength(currNode); 
        	active = currNode;
        	return 1; 
    	}
    	return 0;
 
	}

	void Extensions (int pos) {
		end = pos;
		remainingSuffixCount++;
		lastNew = nullptr;
		while(remainingSuffixCount > 0) {
			if (activeLength == 0) {
				activeEdge = pos;
			}		
			if (active->children[s[activeEdge]] == 0) {
				SufNode* newNode = new SufNode(pos, &end);
				active->children[s[pos]] = newNode;

				if (lastNew != nullptr) {
					lastNew->sufLink = active;
					lastNew = nullptr;
				}
			} else {
				SufNode* next = active->children[s[activeEdge]];		
				if (SkipDown(next)) {
					continue;
				}			
				if (s[next->left + activeLength] == s[pos]) {
					if (lastNew != nullptr && active != root) {
						lastNew->sufLink = active;
						lastNew = nullptr;
					}
					activeLength++;
					break;
				}
				int* splitEnd = new int;
				*splitEnd = next->left + activeLength - 1;
				SufNode* split = new SufNode(next->left, splitEnd);
				split->sufLink = root;//??
				active->children[s[next->left]] = split;
				SufNode* list = new SufNode(pos, &end);
				split->children[s[pos]] = list;
				next->left += activeLength;
				split->children[s[next->left]] = next;
				if (lastNew != nullptr) {
					lastNew->sufLink = split;
				}
				lastNew = split;
			}			
			remainingSuffixCount--;
			if (active == root && activeLength > 0) {
				activeLength--;
				activeEdge = pos - remainingSuffixCount + 1;
			} else if (active != root) {
				active = active->sufLink;
			}
		}
	}

void GetIndex(SufNode *n, int labelHeight) { 	 
    int leaf = 1; 
    for (auto it = n->children.begin(); it != n->children.end(); it++) { 
        leaf = 0; 
        GetIndex(it->second, labelHeight + edgeLength(it->second)); 
    }
    if (leaf == 1) { 
        n->sufIndex = s.size() - labelHeight; 
    } 

} 

	void recSearch(SufNode* node, vector<int> &answ) {
		if (IsLeaf(node)) {
			answ.push_back(node->sufIndex + 1);
		} else {
			for (auto it = node->children.begin(); it != node->children.end(); it++) {
				if (it->second) {
				recSearch(it->second, answ);
				}
			}
		}
	}

	vector<int> Search (SufNode* node, string &str) {
		int i = 0;
		bool out = true;
		vector<int> answer;
		while (out && node->children[str[i]]) {
			node = node->children[str[i]];
			for (int j = node->left; j <= *(node->right); j++, i++){
				if (i == str.size() || str[i] != s[j]) {
					out = false;
					break;
				}
			}
		}
		if (i == str.size()) {
			recSearch(node, answer);
		}
		return answer;
	}

	void Clean (SufNode* node) {
		for (auto it = node->children.begin(); it != node->children.end(); it++) {
			if (it->second) {
        		Clean(it->second);
        	}
    	}
    	if (node != root && !IsLeaf(node)) {
    		delete node->right;
    	}
    	delete node;
    	return;
	}

	SufNode *root;
	string s;
	int end;
	SufNode *active;
	SufNode *lastNew;
	int activeEdge; 
	int activeLength;
	int remainingSuffixCount; 


};

int main() {
	string s, t;
	getline(cin, s, '\n');
	s += "}";
	SufTree tree(s);
	tree.Build();
	int ind = 1;
	while(cin >> t) {
		vector<int> answer;
		if (t.size() > 0 && t.size() < s.size()) {
			answer = tree.TreeSearch(t);
		}
		if (answer.size() > 0) {
			cout << ind << ": ";
			sort(answer.begin(), answer.end());
			for (int i = 0; i < answer.size() - 1; i++) {
				cout << answer[i] << ", ";
			}
			cout << answer[answer.size() - 1] << '\n';
		}
		ind++;
	}
	return 0;
}