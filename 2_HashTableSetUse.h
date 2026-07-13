/*
#include <iostream>
#include "2_HashTableSet.h"
using namespace std;

size_t hashFunction(const int & key){
    return key;
}

int main(){
    // Usa identity hash para ints con hash_int personalizada
    HashTableSet<int> numeros(10, [](const int& key) -> size_t { return key; });
    numeros.insert(5);
    numeros.insert(3);
    numeros.insert(1);
    numeros.insert(4);
    numeros.insert(2);
    numeros.printAll();

    cout<<endl;

    // Usa std::hash<string> automaticamente (sin pasar hash ni comparador)
    HashTableSet<string> palabras;
    palabras.insert("Hola");
    palabras.insert("Mundo");
    palabras.insert("Hash");
    palabras.printAll();

    cout<<endl;

    HashTableSet<int>numeros2(10, hashFunction);
    numeros2.insert(5);
    numeros2.insert(4);
    numeros2.insert(3);
    numeros2.insert(2);
    numeros2.insert(1);
    numeros2.printAll();

    return 0;
}
*/