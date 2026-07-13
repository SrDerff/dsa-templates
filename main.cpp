#include <iostream>
#include "2_HashTableSet.h"
using namespace std;

size_t hash(string st){
    size_t hashedKey=0;
    for(auto ch: st){
        hashedKey+=ch;
    }
    return hashedKey;
}

int main(){
    HashTableSet<int>ht(hash);
    ht.insert(5);
    ht.insert(3);
    ht.insert(1);
    ht.insert(4);
    ht.insert(2);
    ht.dispAll();
    return 0;
}