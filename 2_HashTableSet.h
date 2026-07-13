#include <vector>
#include <list>
#include <algorithm>

/*
Uso:

size_t funcionHash(Objeto obj){
    obj.getVariableParaHash();
    -- APLICAR HASH --
}

HashTable<Objeto>ht(10, funcionHash);
*/

template <typename T>
class HashTableSet {
private:
    //contenedor
    std::vector<std::list<T>> table;
    //numero elementos
    size_t numElements;
    //factor de carga (por defecto 0.75)
    float maxLoadFactor;

    // Puntero a función hash
    size_t (*hashFunction)(const T&);

    //obtener indice de un elemento
    size_t getIndex(const T& value) const {
        return hashFunction(value) % table.size();
    }

    //rehash a la table
    void rehash() {
        //calcula nueva capacidad
        size_t newCapacity = std::max<size_t>(1, table.size() * 2);
        //crea otra table con mas capacidad
        std::vector<std::list<T>> newTable(newCapacity);
        
        //recorre cada lista
        for (const auto& bucket : table) {
            //por cada lista recorre cada elemento existente dentro
            for (const auto& value : bucket) {
                //halla el nuevo indice dentro de la nueva table
                size_t index = hashFunction(value) % newCapacity;
                //guarda el elemento en el nuevo indice
                newTable[index].push_back(value);
            }
        }

        //mueve la nueva tabla a la tabla original
        table = std::move(newTable);
    }

    //si el factor de carga se rompe hace rehash
    void checkLoadFactor() {
        if ((float)numElements / table.size() > maxLoadFactor)
            rehash();
    }

public:
    //constructor
    HashTableSet(size_t capacity,
            size_t (*hash)(const T&),
            float loadFactor = 0.75f)
        : table(std::max<size_t>(1,capacity)),
          numElements(0),
          maxLoadFactor(loadFactor),
          hashFunction(hash) {}

    //insertar elemento
    bool insert(const T& value) {
        //si ya contiene un elemento igual, no inserta
        if (contains(value))
            return false;

        //agrega el elemento a la ultima posicion de la lista en el indice hash
        table[getIndex(value)].push_back(value);
        //aumenta el numerode elementos
        numElements++;
        //verifica el factor de carga, puede hacer rehash
        checkLoadFactor();
        return true;
    }

    //verifica si ya existe un elemento igual en la table
    bool contains(const T& value) const {
        //obtener la lista con el hash del elemento
        const auto& bucket = table[getIndex(value)];

        //busca en la lista si existe el elemento buscado
        for (const auto& x : bucket)
            if (x == value)
                return true;

        return false;
    }

    //borra elemento de la table
    bool erase(const T& value) {
        //obtener la lista con el hash del elemento
        auto& bucket = table[getIndex(value)];

        //busca dentro de la lista
        //it: puntero a posicion inicial
        //mientras la direccion a la que apunta el puntero sea diferente de end()
        //aumenta la direccion con it++
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == value) {
                bucket.erase(it);
                numElements--;
                return true;
            }
        }

        return false;
    }

    //limpia la table
    void clear() {
        //recorre cada lista dentro de la table
        for (auto& bucket : table)
            //vacia la lista
            bucket.clear();

        //reinicia el contador de elementos a cero
        numElements = 0;
    }

    //retonar la cantidad actual de elementos, no la capacidad de la table
    size_t size() const {
        return numElements;
    }

    //retorna si la lista esta vacia o no
    bool empty() const {
        return numElements == 0;
    }
};