#include<iostream>
#include <algorithm>
#include <cassert>

namespace NSimple {

template <typename T>
class TVector {
public:
    using valueType = T;

    TVector(): alreadyUsed(0), storageSize(0), storage(nullptr) {
    }

    TVector(int size, const valueType& defaultValue = valueType()): TVector() {
        assert(size >= 0);

        if (size == 0) {
            return;
        }

        alreadyUsed = size;
        storageSize = size;
        storage = new valueType[size];

        std::fill(storage, storage + alreadyUsed, defaultValue);
    }

    int Size() const {
        return alreadyUsed;
    }

    bool Empty() const {
        return Size() == 0;
    }


    friend void Swap(TVector& lhs, TVector& rhs) {
        using std::swap;

        swap(lhs.alreadyUsed, rhs.alreadyUsed);
        swap(lhs.storageSize, rhs.storageSize);
        swap(lhs.storage, rhs.storage);
    }

    TVector& operator=(TVector other) {
        Swap(*this, other);
        return *this;
    }

    TVector(const TVector& other): TVector() {
        TVector next(other.storageSize);
        next.alreadyUsed = other.alreadyUsed;

        if (other.storage) {
            std::copy(other.storage, other.storage + other.storageSize,
                      next.storage);
        }

        Swap(*this, next);
    }

    ~TVector() {
        delete[] storage;
        storageSize = 0;
        alreadyUsed = 0;
        storage = nullptr;
    }

    void PushBack(const valueType& value) {
        if (alreadyUsed < storageSize) {
            storage[alreadyUsed] = value;
            ++alreadyUsed;
            return;
        }

        int nextSize = 1;
        if (storageSize) {
            nextSize = storageSize * 2;
        }

        TVector next(nextSize);
        next.alreadyUsed = alreadyUsed;

        if (storage) {
            std::copy(storage, storage + storageSize, next.storage);
        }

        next.PushBack(value);
        Swap(*this, next);
    }

    valueType& At(int index) {
        if (index < 0 || index > alreadyUsed) {
            throw std::out_of_range("You are doing this wrong!");
        }

        return storage[index];
    }


    valueType& operator [](int index) {
        return At(index);
    }

private:
    int alreadyUsed;
    int storageSize;
    valueType* storage;
};

}

struct  TKv {
    char phone[20];
    char val[70];
    unsigned long long normPhone;
    
};

using namespace NSimple;

void CountingSort(TVector<TKv> &elems, unsigned long long q) {
    int tmp[10] {0};
    TVector<TKv> out(elems.Size());

    for (int i = 0; i < elems.Size(); ++i) {
  
        ++tmp[(elems[i].normPhone / q) % 10];
       
    }

    for (int i = 1; i < 10; ++i) {   
        tmp[i] += tmp[i-1];
    }
     
    for (int i = elems.Size() - 1; i >= 0; --i) {   
        out[tmp[(elems[i].normPhone / q) % 10] - 1 ] = elems[i];
        tmp[(elems[i].normPhone / q) % 10]--;

    }
    elems = out;
    
}

void RadixSort(TVector<TKv> &elems, unsigned long long max1) {
    
    for (unsigned long long i = 1; max1 / i > 0; i *= 10) {
        CountingSort(elems, i);
        
    }   
   
}

long long Maxi(TVector<TKv> &qu) {
    unsigned long long max = 0; 
    for (int i = 0; i < qu.Size(); ++i) {
        
        if (qu[i].normPhone > max) {

            max = qu[i].normPhone;
        }
    }

        return  max;
}

const int NORMAL_SCANF = 2;

int main() {

    std::ios::sync_with_stdio(false);
    TKv kev;
    TVector<TKv> vec;
    
    
     while (scanf("%s\t%s", kev.phone, kev.val) == NORMAL_SCANF) { 
        vec.PushBack(kev);    
    }
    
    for (int i = 0; i < vec.Size(); ++i) {
        int n = 1;
        unsigned long long a = 0, b = 0;
        while (vec[i].phone[n] != '\0') {
            if (vec[i].phone[n] != '-') {
                a = vec[i].phone[n] - '0';
                b = b * 10 + a;
            }
            ++n;
        }

        vec[i].normPhone = b;

    }
    
    RadixSort(vec, Maxi(vec));

    for(int i = 0; i < vec.Size(); i++) {
        printf("%s\t%s\n",vec[i].phone, vec[i].val);
    }

    return 0;
}