#include <vector>
#include <algorithm>
#include <functional>
#include "2_HashEntidad.h"

template <typename Key, typename Value>
class HashTableMapLP {
private:
    enum class CellState { EMPTY, OCCUPIED, DELETED };

    struct Cell {
        HashEntidad<Key, Value> entidad;
        CellState state = CellState::EMPTY;
    };

    std::vector<Cell> table;
    size_t numElements;
    float maxLoadFactor;

    size_t (*hashFunction)(const Key&);
    bool (*equalTo)(const Key&, const Key&);

    static bool defaultEqualTo(const Key& a, const Key& b) {
        return a == b;
    }

    static size_t defaultHash(const Key& v) {
        return std::hash<Key>{}(v);
    }

    size_t probe(const Key& key) const {
        size_t hash = hashFunction(key);
        for (size_t i = 0; i < table.size(); i++) {
            size_t index = (hash + i) % table.size();
            if (table[index].state == CellState::EMPTY)
                return index;
            if (table[index].state == CellState::OCCUPIED &&
                equalTo(table[index].entidad.key, key))
                return index;
        }
        return table.size();
    }

    size_t findSlot(const Key& key) const {
        size_t hash = hashFunction(key);
        for (size_t i = 0; i < table.size(); i++) {
            size_t index = (hash + i) % table.size();
            if (table[index].state == CellState::EMPTY)
                return table.size();
            if (table[index].state == CellState::OCCUPIED &&
                equalTo(table[index].entidad.key, key))
                return index;
        }
        return table.size();
    }

    void rehash() {
        size_t newCapacity = std::max<size_t>(1, table.size() * 2);
        std::vector<Cell> oldTable = std::move(table);
        table = std::vector<Cell>(newCapacity);
        numElements = 0;

        for (const auto& cell : oldTable) {
            if (cell.state == CellState::OCCUPIED)
                insert(cell.entidad.key, cell.entidad.value);
        }
    }

    void checkLoadFactor() {
        if ((float)numElements / table.size() > maxLoadFactor)
            rehash();
    }

public:
    HashTableMapLP(size_t capacity = 10,
            size_t (*hash)(const Key&) = defaultHash,
            bool (*equal)(const Key&, const Key&) = defaultEqualTo,
            float loadFactor = 0.5f)
        : table(std::max<size_t>(1, capacity)),
          numElements(0),
          maxLoadFactor(loadFactor),
          hashFunction(hash),
          equalTo(equal) {}

    bool insert(const Key& key, const Value& value) {
        if (numElements == table.size()) rehash();

        size_t index = probe(key);
        if (index == table.size()) return false;

        if (table[index].state == CellState::OCCUPIED &&
            equalTo(table[index].entidad.key, key))
            return false;

        table[index].entidad.key = key;
        table[index].entidad.value = value;
        table[index].state = CellState::OCCUPIED;
        numElements++;
        checkLoadFactor();
        return true;
    }

    bool contains(const Key& key) const {
        return findSlot(key) != table.size();
    }

    Value* find(const Key& key) {
        size_t index = findSlot(key);
        if (index == table.size()) return nullptr;
        return &table[index].entidad.value;
    }

    bool erase(const Key& key) {
        size_t index = findSlot(key);
        if (index == table.size()) return false;

        table[index].state = CellState::DELETED;
        numElements--;
        return true;
    }

    Value& operator[](const Key& key) {
        auto* found = find(key);
        if (found) return *found;

        if (numElements == table.size()) rehash();

        size_t index = probe(key);
        table[index].entidad.key = key;
        table[index].entidad.value = Value{};
        table[index].state = CellState::OCCUPIED;
        numElements++;
        checkLoadFactor();
        return table[index].entidad.value;
    }

    void clear() {
        for (auto& cell : table)
            cell.state = CellState::EMPTY;
        numElements = 0;
    }

    size_t size() const {
        return numElements;
    }

    bool empty() const {
        return numElements == 0;
    }

    void printAll() const {
        for (size_t pos = 0; pos < table.size(); pos++) {
            std::cout << "Key: " << pos << " | ";
            if (table[pos].state == CellState::OCCUPIED)
                std::cout << table[pos].entidad.key << " -> " << table[pos].entidad.value;
            else if (table[pos].state == CellState::DELETED)
                std::cout << "(DELETED)";
            std::cout << std::endl;
        }
    }
};
