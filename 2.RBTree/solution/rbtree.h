#ifndef RB_TREE_H
#define RB_TREE_H

#include<iostream>
#include<cstring>
#include<fstream>

const int STR_SIZE = 257;

class TRBTree {

public:

    TRBTree() : size(0) {
            nil = new TNode();
            root = nil;
    }

    ~TRBTree() {
            CleanAll(root);
            delete nil;
            size = 0;
    }

    void RBInsert(char* in, unsigned long long v) {
        TNode* q = root;
        while(q != nil && strcmp(q->key, in) != 0) {
            if(strcmp(in, q->key) < 0) {
                q = q->left;
            } else {
                q = q->right;
            }
        }
        if (q != nil) {  
            printf("Exist\n");
            delete [] in;
            return;
        }
        TNode* z = new TNode(in,v);
        TNode* y = nil;
        TNode* x = root;
        while (x != nil) {
            y = x;
            if (strcmp(z->key, x->key) < 0) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == nil) {
            root = z;
        } else if (strcmp(z->key, y->key) < 0) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = 0;
        FixInsert(z);
        size++;
        printf("OK\n");
    }

    void RBDelete(char* k){
        TNode* z = root;
        while (z != nil && strcmp(z->key, k) != 0) {
            if (strcmp(k, z->key) < 0) {
                z = z->left;
            } else {
                z = z->right;
            }
        }
        if (z == nil){  
            printf("NoSuchWord\n");
            return;
        }
        TNode* y = z;
        TNode* x = nil;
        int trueColor = y->color;
        if (z->left == nil) {
            x = z->right;
            Transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            Transplant(z, z->left);
        } else {
            y = TreeMin(z->right);
            trueColor = y->color;
            x = y->right;
            if (y->p == z) {
                x->p = y;
            } else {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            Transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        if (trueColor == 1) {
            DeleteFix(x);
        }
        delete [] z->key;
        delete z;
        size--;
        printf("OK\n");
    }

    void RBPrint() {
        RecPrint(root);
    }

    void RBFind(char* k) {
        TNode* tmp = root;
        while (tmp != nil && strcmp(tmp->key, k) != 0) {
            if (strcmp(k, tmp->key) < 0) {
                tmp = tmp->left;
            } else {
                tmp = tmp->right;
            }
        }
        if (tmp == nil) {
            printf("NoSuchWord\n");
        } else {        
            printf("OK: %llu\n", tmp->val);
        }
    }

   void TreeSave(char* file) {
        FILE* f = fopen(file, "w");
        if (f == NULL) {
            fprintf(stderr, "ERROR: can`t open file\n");
        }
        KLP(root, f);
        printf("OK\n");
        if (fclose(f)) {
            fprintf(stderr, "can`t close file\n");
        }
    }

    void TreeLoad(char* file) {
        FILE* f = fopen(file, "r");
        if (f == NULL) {
            fprintf(stderr, "ERROR: can`t open file\n");
        }
        Clean();
        root = Load(f, nil);
        printf("OK\n");
        if (fclose(f)) {
            fprintf(stderr, "can`t close file\n");
        }
    }

    void Clean() {
        CleanAll(root);
        size = 0;
    }

private:
    struct TNode {
        char* key;
        unsigned long long val;
        int color;
        TNode *left;
        TNode *right;
        TNode *p;

        TNode():
                key(), val(), color(1),
                left(nullptr), right(nullptr), p(nullptr)
                {
                }

        TNode (char* k, unsigned long long v):
                key(k), val(v), color(1),
                left(nullptr), right(nullptr), p(nullptr)
                {
                }
    };

    TNode* root;
    int size;
    TNode* nil;

    void CleanAll(TNode* root) {
        if (root == nil) {
            return;
        }
        CleanAll(root->left);
        CleanAll(root->right);
        delete [] root->key;
        delete root;
    }

    void LeftRotate(TNode* x) {
        TNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            root = y;
        } else if(x == x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
        y->left = x;
        x->p = y;
    }

    void RightRotate(TNode* x) {
        TNode* y = x->left;
        x->left = y->right;
        if (y->right != nil) {
            y->right->p = x;
        }
        y->p = x->p;
        if (x->p == nil){
            root = y;
        } else if (x == x->p->right) {
            x->p->right = y;
        } else {
            x->p->left = y;
        }   
        y->right = x;
        x->p = y;
    }

    void FixInsert(TNode *z) {
        TNode* y = nil;
        while (z->p->color == 0) {
            if (z->p == z->p->p->left) {
                y = z->p->p->right;  
                if (y->color == 0) {
                    z->p->color = 1;
                    y->color = 1;
                    z->p->p->color = 0;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->right) {
                        z = z->p;
                        LeftRotate(z);
                    }
                    z->p->color = 1;
                    z->p->p->color = 0;
                    RightRotate(z->p->p);
                }
            } else {
                y = z->p->p->left;  
                if (y->color == 0) {
                    z->p->color = 1;
                    y->color = 1;
                    z->p->p->color = 0;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->left) {
                        z = z->p;
                        RightRotate(z);
                    }
                    z->p->color = 1;
                    z->p->p->color = 0;
                    LeftRotate(z->p->p);
                }
            }
        }
        root->color = 1;
    }

    TNode* TreeMin(TNode* x) {
        TNode* tmp = x;
        TNode* res = nil;
        while (tmp != nil) {
            res = tmp;
            tmp = tmp->left;
        }
        return res;
    }

    void RecPrint(TNode* rt) {
        if (rt == nil) {
            return;
        }
        RecPrint(rt->right);
        printf("%s\n", rt->key);
        RecPrint(rt->left);
    }

    void Transplant(TNode* u,TNode* v){
        if (u->p == nil) {
            root = v;
        } else if (u == u->p->left) {
            u->p->left = v;
        } else {
            u->p->right = v;
        }
        v->p = u->p;
    }

    void DeleteFix(TNode* x) {
        while ((x != root) && (x->color == 1)) {
            if (x == x->p->left) {
                TNode* w = x->p->right;
                if (w->color == 0) {
                    w->color = 1;
                    x->p->color = 0;
                    LeftRotate(x->p);
                    w = x->p->right;
                }
                if ((w->left->color == 1) && (w->right->color == 1)) {
                    w->color = 0;
                    x = x->p;
                } else {
                    if (w->right->color == 1) {
                        w->left->color = 1;
                        w->color = 0;
                        RightRotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = 1;
                    w->right->color = 1;
                    LeftRotate(x->p);
                    x = root;
                }
            } else {
                TNode* w = x->p->left;
                if (w->color == 0) {
                    w->color = 1;
                    x->p->color = 0;
                    RightRotate(x->p);
                    w = x->p->left;
                }
                if ((w->right->color == 1) && (w->left->color == 1)) {
                    w->color = 0;
                    x = x->p;
                } else {
                    if (w->left->color == 1) {
                        w->right->color = 1;
                        w->color = 0;
                        LeftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = 1;
                    w->left->color = 1;
                    RightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = 1;
    }

void KLP(TNode* n, FILE* f) {
        int a = 1;
        int b = 0;
        if (n == nil){
            return;
        } else {
            fwrite(n->key, STR_SIZE, sizeof(n->key[0]), f);   
        }
        fwrite(&n->val, sizeof(n->val), 1, f);   
        fwrite(&n->color, sizeof(n->color), 1, f);   
        if (n->left != nil) {
            fwrite(&a, sizeof(a), 1, f); 
        } else {
            fwrite(&b, sizeof(b), 1, f); 
        }
        if (n->right != nil) {
            fwrite(&a, sizeof(a), 1, f); 
        } else {
            fwrite(&b, sizeof(b), 1, f); 
        }
            KLP(n->left, f);
            KLP(n->right, f);
        return;
    }

    TNode* Load(FILE* f, TNode* parent) {
        TNode* root;
        char* k = new char[STR_SIZE];
        unsigned long long vl;
        int clr;
        int lChild, rChild;
        if(!(fread(k, STR_SIZE, 1, f))) {
            delete [] k;
            return nil;
        }
        fread(&vl, sizeof(vl), 1,f);
        fread(&clr, sizeof(clr), 1,f);
        fread(&lChild, sizeof(lChild), 1,f);
        fread(&rChild, sizeof(rChild), 1,f);
        root = new TNode(k,vl);
        size++;
        root->color = clr;
        root->p = parent;
        if (lChild == 0) {
            root->left = nil;
        } else {
            root->left = Load(f, root);
        }
        if (rChild == 0) {
            root->right = nil;
        } else {
            root->right = Load(f, root);
        }
        return root;
    }
};

#endif