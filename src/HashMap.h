#ifndef DUNGEONGAME_HASHMAP_H
#define DUNGEONGAME_HASHMAP_H

#include "iostream"

using namespace std;

template<class K, class V>
class MapNode {
    K _key;
    V _value;
public:
    MapNode(K &key, V &value) {
        _key = key;
        _value = value;
    }

    MapNode() {}

    K getKey() const {
        return _key;
    }

    V getValue() const {
        return _value;
    }

    void setValue(V value) {
        _value = value;
    }
};

template<class K, class V>
class HashMap {
    MapNode<K, V> *array;

    int _capacity;
    int _size;

    void sort() {
        for (int i = 1; i < size(); i++) {
            for (int j = i; j > 0 && array[j - 1].getKey() > array[j].getKey(); j--) {
                MapNode<K, V> tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }

public:
    HashMap() {
        array = new MapNode<K, V>[1];
        _capacity = 1;
        _size = 0;
    }

    void push(K key, V value) {
        if (!contains(key)) {
            if (_size == _capacity) {
                auto *temp = new MapNode<K, V>[2 * _capacity];

                for (int i = 0; i < _capacity; ++i) {
                    temp[i] = array[i];
                }

                delete[] array;
                _capacity *= 2;
                array = temp;
            }
            array[_size] = MapNode<K, V>(key, value);
            _size++;
            sort();

        }
    }

    V get(K key) {
        int index;
        if (contains(key, index)) {
            return array[index].getValue();
        } else {
            cout << "\nThere is no value with key \"" << key << "\"";
        }
    }

    bool contains(K key, int &index) {
        int l = 0, r = size(), mid;

        while (l < r) {
            mid = (l + r) / 2;
            if (array[mid].getKey() > key) r = mid;
            else l = mid + 1;
        }
        r--;

        if (array[r].getKey() == key) {
            index = r;
            return true;
        }
    }

    bool contains(K key) {
        int l = 0, r = size(), mid;

        while (l < r) {
            mid = (l + r) / 2;
            if (array[mid].getKey() > key) r = mid;
            else l = mid + 1;
        }
        r--;

        if (array[r].getKey() == key) {
            return true;
        }
    }

    int size() { return _size; }

    int capacity() { return _capacity; }

    void print() {
        for (int i = 0; i < size(); ++i) {
            cout << "{\"";
            cout << array[i].getKey();
            cout << "\"";
            cout << ": \"";
            cout << array[i].getValue();
            cout << "\"}\n";
        }
    }
};

#endif
