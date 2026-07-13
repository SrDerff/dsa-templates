#include <vector>
using namespace std;

template<typename T>
class Heap{
private:
    //bucket almacena todos los nodos
    vector<T>bucket;
    //obtener indice padre
    int parent(int index){return (index-1)/2;}
    //obtener indice hijo izquierdo
    int leftChild(int index){return index*2+1;}
    //obtener indice hijo derecho
    int rightChild(int index){return index*2+2;}

    //comparador (define si es max o min heap)
    bool (*comp)(T a, T b);
    
    //ordenar subarbol (padre, hijo izq, hijo der)
    void heapifyDown(vector<T>&vec, int index, int limitIndex){
        //obtener indices hijos
        int left=leftChild(index);
        int right=rightChild(index);

        //hallar el nodo mayor
        int priorChild=index;
        if(left<limitIndex && comp(vec[left],vec[priorChild])){
            priorChild=left;
        }
        if(right<limitIndex && comp(vec[right],vec[priorChild])){
            priorChild=right;
        }
        //si el nodo mayor es diferente al padre, hacer swap
        //y seguir comprobando hacia abajo los subarboles
        if(priorChild!=index){
            swap(vec[priorChild],vec[index]);
            heapifyDown(vec, priorChild, limitIndex);
        }
    }

    //ordenar hacia arriba (hijo, padre)
    void heapifyUp(vector<T>&vec, int index){
        //verificar si ya se llegó a la raiz
        if(index==0) return;
        //hallar indice del padre
        int parentIndex=parent(index);
        //si el nodo rompe la propiedad, se intercambia con el padre
        if(comp(vec[index],vec[parentIndex])){
            swap(vec[index], vec[parentIndex]);
            heapifyUp(vec, parentIndex);
        }
    }
public:
    Heap(bool(*comparador)(T a, T b)){
        comp=comparador;
    }
    Heap(vector<T>vec, bool(*comparador)(T a, T b)){
        int length=vec.size();
        comp=comparador;
        //recorrer desde el ultimo nodo padre hacia atras
        for(int i=length/2-1;i>=0;i--){
            //verificar subarbol hacia abajo
            heapifyDown(vec, i, length);
        }
        bucket=vec;
    }
    void push(T elem){
        //se agrega el nodo al final
        bucket.push_back(elem);
        //se verifica hacia arriba
        heapifyUp(bucket, bucket.size()-1);
    }
    void pop(){
        //se pasa el ultimo nodo a la raiz
        bucket[0]=bucket.back();
        //se elimina el ultimo nodo
        bucket.pop_back();
        //se verifica desde raiz hacia abajo
        heapifyDown(bucket, 0, bucket.size());
    }
    vector<T> heapSort(){
        //copiar el heap a otro vector
        vector<T>vec=bucket;
        //recorrer desde el ultimo hijo hacia atras
        for(int i=vec.size()-1;i>0;i--){
            //colocar el mayot al final
            swap(vec[0],vec[i]);
            //verificar arbol desde la raiz
            heapifyDown(vec, 0, i);
        }
        return vec;
    }
    T top(){
        //devuelve el nodo de la raiz
        return bucket[0];
    }
};