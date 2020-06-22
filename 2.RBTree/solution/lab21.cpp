#include <cctype>
#include "rbtree.h"

struct TKV{
    char key[STR_SIZE];
    unsigned long long value;
};

void Low(char* p) {
    while(*p) {
        if (*p <= 'Z') {
            *p += 'a' - 'A';
        }
        p++;
    }
    return;
}

int main() {
    TRBTree Tree;
    TKV in;
    char c = '0';
    char str[5];
    char str1[25];
    while(c != EOF) {
        do { 
            c = getchar();
        } while (c == '\n' || c == '\t' || c == ' ');
        if(c == '+') {
            char* k =  new char[STR_SIZE];
            std::fill(k, k + 257, '\0');
            scanf("%s %llu", k, &in.value);
            Low(k);
            Tree.RBInsert(k, in.value);
        } else if (c == '-') {
            scanf("%s", in.key);
            Low(in.key);
            Tree.RBDelete(in.key);
        } else if (c == '!') {
            scanf("%s %s", str, str1);
            if (str[0] == 'S') { 
                Tree.TreeSave(str1);

            } else {
                Tree.TreeLoad(str1);
            }
        } else {
            if (c == EOF) {
                break;
            }
            int i = 0;
            while (c != '\n' && c != '\t' && c != ' ')  {
                in.key[i] = c;
                i++;
                c = getchar();
            }
            in.key[i] = '\0';
            Low(in.key);
            Tree.RBFind(in.key);
        }
    }
    return 0;
}