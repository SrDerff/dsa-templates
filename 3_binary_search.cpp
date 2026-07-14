#include <iostream>
#include <vector>
using namespace std;

template<typename T>
int binarySearch(vector<T>v, T valorBuscado, int(*evaluarIgualdad)(T,T)){
    if(v.size()==0) return -1;
    int minIndex=0, maxIndex=v.size()-1;
    while(minIndex<=maxIndex){
        int midIndex=(maxIndex+minIndex)/2;
        int result=evaluarIgualdad(valorBuscado, v[midIndex]);
        if(result<0){
            maxIndex=midIndex-1;
        }
        else if(result>0){
            minIndex=midIndex+1;
        }
        if(result==0){
            return midIndex;
        }
    }
    return -1;
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

int main(){
    vector<int>v={1,2,3,4,5};
    //ORDENAR ANTES DE LLAMAR
    //muestra como si los indices empezaran desde 1, no desde 0 (quitar el +1 del final para que muestre desde 0)
    cout<<"Valor encontrado en la posicion: "<<binarySearch(v, 5, evaluarIgualdad) +1;
    return 0;
}