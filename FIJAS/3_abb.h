#include<functional>
using namespace std;
template<typename T>
class Nodo{
  public:
    T elemento;
    Nodo* izq;
    Nodo* der;
};
template<typename T>
class ArbolBB{
    typedef function<int(T,T)> Comp;//lambda
    Nodo<T>* raiz;
    void(*procesar)(T);//Puntero a función
    Comp comparar;//lambda criterio de comparación

private:
    bool _buscar(Nodo<T>* nodo,T e){
        if(nodo==nullptr) return false;
        else{
            int r= comparar(nodo->elemento,e);
            if(r==0) return true;
            else if(r<0){
                return _buscar(nodo->der,e);
            }
            else{
                return _buscar(nodo->izq,e);
            }
        }
    }
    bool _insertar(Nodo<T>*& nodo,T e){
        if(nodo==nullptr){
            nodo = new Nodo<T>();
            nodo->elemento =e;
            return true;
        }
        else{
            int r= comparar(nodo->elemento,e);
            if(r==0) return false;
            else if(r<0){
                return _insertar(nodo->der,e);
            }
            else{
                return _insertar(nodo->izq,e);
            }
        }
    }
    void _enOrden(Nodo<T>* nodo){
        if(nodo==nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }
    void _preOrden(Nodo<T>* nodo){
        if(nodo==nullptr) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }
    void _postOrden(Nodo<T>* nodo){
        if(nodo==nullptr) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }
    bool _vacio(){
        return raiz==nullptr;
    }
    int _cantidad(Nodo<T>* nodo){
        if(nodo==nullptr) return 0;
        else{
            int ci,cd;
            ci = _cantidad(nodo->izq);
            cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }
    }
    int _altura(Nodo<T>* nodo){
        if(nodo==nullptr) return 0;
        else{
            int ai,ad;
            ai = 1 + _altura(nodo->izq);
            ad = 1 + _altura(nodo->der);
            return ai>ad ?ai:ad;
        }
    }
    
    int _minimo(Nodo<T>* nodo){
        if(nodo->izq==nullptr) 
            return nodo->elemento;
        else 
        return _minimo(nodo->izq);
    }
    int _maximo(Nodo<T>* nodo){
        if(nodo->der==nullptr) 
            return nodo->elemento;
        else 
        return _maximo(nodo->der);
    }
    
    public:
        ArbolBB(void(*otroPunteroAFuncion)(T)){
            this->procesar = otroPunteroAFuncion;
            this->comparar = [](T a,T b)->int {return a - b;};
            raiz=nullptr;
        }
        bool insertar(T e){
            return _insertar(raiz,e);
        }
        void enOrden(){
            _enOrden(raiz);
        }
        void preOrden(){
            _preOrden(raiz);
        }
        void postOrden(){
            _postOrden(raiz);
        }
        int cantidad(){
            return _cantidad(raiz);
        }
        int altura(){
            return _altura(raiz);
        }
        bool buscar(T e){
            return _buscar(raiz,e);
        }
        int minimo(){
            return _minimo(raiz);
        }
        int maximo(){
            return _maximo(raiz);
        }
    
};



