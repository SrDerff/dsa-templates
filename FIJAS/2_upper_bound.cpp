#include <iostream>
#include <vector>
using namespace std;

template<typename T>
int upperBound(vector<T> v,
               T valorBuscado,
               int(*comparar)(T,T))
{
    int minIndex = 0;
    int maxIndex = v.size()-1;
    int respuesta = v.size();

    while(minIndex <= maxIndex){
        int midIndex = (minIndex + maxIndex)/2;

        if(comparar(v[midIndex], valorBuscado) <= 0){
            minIndex = midIndex + 1;
        }
        else{
            respuesta = midIndex;
            maxIndex = midIndex - 1;
        }
    }

    return respuesta;
}

//numeros
int evaluarIgualdad(int a, int b){
    return a-b;
}

//strings
int evaluarIgualdadString(string a, string b){
    if(a<b) return -1;
    if(a>b) return 1;
    return 0;
}

/*
Primer elemento ≥ x → lowerBound(x)
Primer elemento > x → upperBound(x)
Último elemento ≤ x → upperBound(x)-1
Último elemento < x → lowerBound(x)-1
*/

int main(){
    vector<int> v = {1,2,2,2,4,5};
    //PRIMERA POSICION MAYOR A n
    cout << upperBound(v, 2, evaluarIgualdad);
}