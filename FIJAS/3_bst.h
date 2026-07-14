#pragma once

template<typename T>
class NodoBST {
public:
    T data;
    NodoBST *left, *right;
    NodoBST(const T& e) : data(e), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
    NodoBST<T>* root;
    bool (*comp)(const T&, const T&);
    void (*procesar)(const T&);
    
    void _insertar(NodoBST<T>*& nodo, const T& e) {
        if (nodo == nullptr) {
            nodo = new NodoBST<T>(e);
            return;
        }
        // Si son iguales (comp retorna false en ambos sentidos),
        // inserta a la derecha para permitir duplicados
        if (comp(e, nodo->data))
            _insertar(nodo->left, e);
        else
            _insertar(nodo->right, e);
    }

    bool _buscar(NodoBST<T>* nodo, const T& e) const {
        if (nodo == nullptr) return false;
        if (comp(e, nodo->data))
            return _buscar(nodo->left, e);
        else if (comp(nodo->data, e))
            return _buscar(nodo->right, e);
        else
            return true;
    }

    NodoBST<T>* _minNodo(NodoBST<T>* nodo) const {
        while (nodo && nodo->left)
            nodo = nodo->left;
        return nodo;
    }

    bool _eliminar(NodoBST<T>*& nodo, const T& e) {
        if (nodo == nullptr) return false;
        if (comp(e, nodo->data))
            return _eliminar(nodo->left, e);
        else if (comp(nodo->data, e))
            return _eliminar(nodo->right, e);
        else {
            NodoBST<T>* temp = nodo;
            if (nodo->left == nullptr) {
                nodo = nodo->right;
                delete temp;
            } else if (nodo->right == nullptr) {
                nodo = nodo->left;
                delete temp;
            } else {
                temp = _minNodo(nodo->right);
                nodo->data = temp->data;
                _eliminar(nodo->right, temp->data);
            }
            return true;
        }
    }

    T* _minimo(NodoBST<T>* nodo) const {
        if (nodo == nullptr) return nullptr;
        while (nodo->left)
            nodo = nodo->left;
        return &nodo->data;
    }

    T* _maximo(NodoBST<T>* nodo) const {
        if (nodo == nullptr) return nullptr;
        while (nodo->right)
            nodo = nodo->right;
        return &nodo->data;
    }

    void _enOrden(NodoBST<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->left);
        procesar(nodo->data);
        _enOrden(nodo->right);
    }

    void _preOrden(NodoBST<T>* nodo) {
        if (nodo == nullptr) return;
        procesar(nodo->data);
        _preOrden(nodo->left);
        _preOrden(nodo->right);
    }

    void _postOrden(NodoBST<T>* nodo) {
        if (nodo == nullptr) return;
        _postOrden(nodo->left);
        _postOrden(nodo->right);
        procesar(nodo->data);
    }

    int _cantidad(NodoBST<T>* nodo) const {
        if (nodo == nullptr) return 0;
        return 1 + _cantidad(nodo->left) + _cantidad(nodo->right);
    }

    int _altura(NodoBST<T>* nodo) const {
        if (nodo == nullptr) return 0;
        int ai = 1 + _altura(nodo->left);
        int ad = 1 + _altura(nodo->right);
        return ai > ad ? ai : ad;
    }

    int _sumar(NodoBST<T>* nodo, int (*extraer)(const T&)) const {
        if (nodo == nullptr) return 0;
        return _sumar(nodo->left, extraer) +
               extraer(nodo->data) +
               _sumar(nodo->right, extraer);
    }

    int _sumarRango(NodoBST<T>* nodo, int (*extraer)(const T&), int min, int max) const {
        if (nodo == nullptr) return 0;
        int val = extraer(nodo->data);
        int suma = (val >= min && val <= max) ? val : 0;
        return suma + _sumarRango(nodo->left, extraer, min, max) +
                      _sumarRango(nodo->right, extraer, min, max);
    }

    int _contarRango(NodoBST<T>* nodo, int (*extraer)(const T&), int min, int max) const {
        if (nodo == nullptr) return 0;
        int val = extraer(nodo->data);
        int count = (val >= min && val <= max) ? 1 : 0;
        return count + _contarRango(nodo->left, extraer, min, max) +
                       _contarRango(nodo->right, extraer, min, max);
    }

public:
    BST(bool (*c)(const T&, const T&), void (*p)(const T&))
        : root(nullptr), comp(c), procesar(p) {}

    void insertar(const T& e) {
        _insertar(root, e);
    }

    bool buscar(const T& e) const {
        return _buscar(root, e);
    }

    bool eliminar(const T& e) {
        return _eliminar(root, e);
    }

    void enOrden() {
        _enOrden(root);
    }

    void preOrden() {
        _preOrden(root);
    }

    void postOrden() {
        _postOrden(root);
    }

    int cantidad() const {
        return _cantidad(root);
    }

    int altura() const {
        return _altura(root);
    }

    bool vacio() const {
        return root == nullptr;
    }

    T* minimo() const {
        return _minimo(root);
    }

    T* maximo() const {
        return _maximo(root);
    }

    int sumar(int (*extraer)(const T&)) const {
        return _sumar(root, extraer);
    }

    int sumarRango(int (*extraer)(const T&), int min, int max) const {
        return _sumarRango(root, extraer, min, max);
    }

    int contar() const {
        return _cantidad(root);
    }

    int contarRango(int (*extraer)(const T&), int min, int max) const {
        return _contarRango(root, extraer, min, max);
    }
};
