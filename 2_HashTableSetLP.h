#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class HashTableSetLP {
private:
    enum class CellState { EMPTY, OCCUPIED, DELETED };

    struct Cell {
        T value;
        CellState state = CellState::EMPTY;
    };

    std::vector<Cell> table;
    size_t numElements;
    float maxLoadFactor;

    size_t (*hashFunction)(const T&);
    bool (*equalTo)(const T&, const T&);

    static bool defaultEqualTo(const T& a, const T& b) {
        return a == b;
    }

    static size_t defaultHash(const T& v) {
        return std::hash<T>{}(v);
    }

    bool isSlotUsable(size_t index) const {
        return table[index].state == CellState::EMPTY ||
               table[index].state == CellState::DELETED;
    }

    size_t probe(const T& value) const {
        size_t hash = hashFunction(value);
        for (size_t i = 0; i < table.size(); i++) {
            size_t index = (hash + i) % table.size();
            if (table[index].state == CellState::EMPTY)
                return index;
            if (table[index].state == CellState::OCCUPIED &&
                equalTo(table[index].value, value))
                return index;
        }
        return table.size();
    }

    size_t findSlot(const T& value) const {
        size_t hash = hashFunction(value);
        for (size_t i = 0; i < table.size(); i++) {
            size_t index = (hash + i) % table.size();
            if (table[index].state == CellState::EMPTY)
                return table.size();
            if (table[index].state == CellState::OCCUPIED &&
                equalTo(table[index].value, value))
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
                insert(cell.value);
        }
    }

    void checkLoadFactor() {
        if ((float)numElements / table.size() > maxLoadFactor)
            rehash();
    }

public:
    HashTableSetLP(size_t capacity = 10,
            size_t (*hash)(const T&) = defaultHash,
            bool (*equal)(const T&, const T&) = defaultEqualTo,
            float loadFactor = 0.5f)
        : table(std::max<size_t>(1, capacity)),
          numElements(0),
          maxLoadFactor(loadFactor),
          hashFunction(hash),
          equalTo(equal) {}

    bool insert(const T& value) {
        if (numElements == table.size()) rehash();

        size_t index = probe(value);
        if (index == table.size()) return false;

        if (table[index].state == CellState::OCCUPIED &&
            equalTo(table[index].value, value))
            return false;

        table[index].value = value;
        table[index].state = CellState::OCCUPIED;
        numElements++;
        checkLoadFactor();
        return true;
    }

    bool contains(const T& value) const {
        size_t index = findSlot(value);
        return index != table.size();
    }

    bool erase(const T& value) {
        size_t index = findSlot(value);
        if (index == table.size()) return false;

        table[index].state = CellState::DELETED;
        numElements--;
        return true;
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
                std::cout << table[pos].value;
            else if (table[pos].state == CellState::DELETED)
                std::cout << "(DELETED)";
            std::cout << std::endl;
        }
    }
};
