#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include "2_HashEntidad.h"

template <typename Key, typename Value>
class HashTableMap {
private:
    std::vector<std::list<HashEntidad<Key, Value>>> table;
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

    size_t getIndex(const Key& key) const {
        return hashFunction(key) % table.size();
    }

    void rehash() {
        size_t newCapacity = std::max<size_t>(1, table.size() * 2);
        std::vector<std::list<HashEntidad<Key, Value>>> newTable(newCapacity);

        for (const auto& bucket : table) {
            for (const auto& entidad : bucket) {
                size_t index = hashFunction(entidad.key) % newCapacity;
                newTable[index].push_back(entidad);
            }
        }

        table = std::move(newTable);
    }

    void checkLoadFactor() {
        if ((float)numElements / table.size() > maxLoadFactor)
            rehash();
    }

public:
    HashTableMap(size_t capacity = 10,
            size_t (*hash)(const Key&) = defaultHash,
            bool (*equal)(const Key&, const Key&) = defaultEqualTo,
            float loadFactor = 0.75f)
        : table(std::max<size_t>(1, capacity)),
          numElements(0),
          maxLoadFactor(loadFactor),
          hashFunction(hash),
          equalTo(equal) {}

    bool insert(const Key& key, const Value& value) {
        if (contains(key))
            return false;

        table[getIndex(key)].push_back(HashEntidad<Key, Value>(key, value));
        numElements++;
        checkLoadFactor();
        return true;
    }

    bool contains(const Key& key) const {
        const auto& bucket = table[getIndex(key)];

        for (const auto& entidad : bucket)
            if (equalTo(entidad.key, key))
                return true;

        return false;
    }

    Value* find(const Key& key) {
        auto& bucket = table[getIndex(key)];

        for (auto& entidad : bucket)
            if (equalTo(entidad.key, key))
                return &entidad.value;

        return nullptr;
    }

    bool erase(const Key& key) {
        auto& bucket = table[getIndex(key)];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (equalTo(it->key, key)) {
                bucket.erase(it);
                numElements--;
                return true;
            }
        }

        return false;
    }

    Value& operator[](const Key& key) {
        auto* found = find(key);
        if (found)
            return *found;

        table[getIndex(key)].push_back(HashEntidad<Key, Value>(key, Value{}));
        numElements++;
        checkLoadFactor();

        auto& bucket = table[getIndex(key)];
        return bucket.back().value;
    }

    void clear() {
        for (auto& bucket : table)
            bucket.clear();
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
            for (const auto& entidad : table[pos])
                std::cout << entidad.key << " -> " << entidad.value << ", ";
            std::cout << std::endl;
        }
    }
};
