template<typename T>
class Nodo{
  public:
    T elemento;
    Nodo *izq;
    Nodo *der;
};

template<typename T>
class ArbolB{
    Nodo<T>* raiz;
    void(*procesar)(T);//Puntero a función
    private:
        void _insertar(Nodo<T>*& nodo,T e){
            if(nodo==nullptr){
                nodo = new Nodo<T>();
                nodo->elemento =e;
            }
            else if(e<nodo->elemento){
                return _insertar(nodo->izq,e);
            }
            else if(e>=nodo->elemento){
                return _insertar(nodo->der,e);
            }
        }
        void _enOrden(Nodo<T>* nodo){ //izquierda,raiz,derecha
            if(nodo==nullptr) return; //si el nodo está vacío
            _enOrden(nodo->izq); //recorrer todos los nodos por la izquierda
            procesar(nodo->elemento); //imprimir el elemento del nodo
            _enOrden(nodo->der); //recorrer todos los nodos de la derecha
        }
        void _preOrden(Nodo<T>* nodo){ //raiz,izquierda, derecha
            if(nodo==nullptr) return; //si el nodo está vacío
            procesar(nodo->elemento); //imprimir el elemento del nodo
            _preOrden(nodo->izq); //recorrer todos los nodos por la izquierda
            _preOrden(nodo->der); //recorrer todos los nodos de la derecha
        }
        void _postOrden(Nodo<T>* nodo){ //izquierda, derecha,raiz
            if(nodo==nullptr) return; //si el nodo está vacío
            _postOrden(nodo->izq); //recorrer todos los nodos por la izquierda
            _postOrden(nodo->der); //recorrer todos los nodos de la derecha
            procesar(nodo->elemento); //imprimir el elemento del nodo
        }
        bool _vacio(){
            return raiz==nullptr;
        }
        int _cantidad(Nodo<T>* nodo){
            //la cantidad de nodos del árbol es:
            //cero si es vacio
            //uno + la cantidad de nodos por la izquierda + cantidad nodos derecha
            if(nodo==nullptr) return 0;
            else{
                int ci,cd;
                ci = _cantidad(nodo->izq);
                cd = _cantidad(nodo->der);
                return 1+ ci + cd;
            }
        }
        int _altura(Nodo<T>* nodo){
            //La altura del árbol es:
            //cero si es vacio
            //la mayor de las altura por la izquierda y por la derecha
            if(nodo==nullptr) return 0;
            else{
                int ai,ad;
                ai = 1 + _altura(nodo->izq);
                ad = 1 + _altura(nodo->der);
                return ai>ad ? ai:ad;
            }
        }
        public:
            ArbolB(void(*otroPunteroAFuncion)(T)){
                this->procesar = otroPunteroAFuncion;
                raiz=nullptr;
            }
            void insertar(T e){
                _insertar(raiz,e);
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
};