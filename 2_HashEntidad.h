#ifndef HASH_ENTIDAD_H
#define HASH_ENTIDAD_H

template <typename Key, typename Value>
class HashEntidad {
public:
    Key key;
    Value value;

    HashEntidad() = default;
    HashEntidad(const Key& k, const Value& v) : key(k), value(v) {}
};

#endif
