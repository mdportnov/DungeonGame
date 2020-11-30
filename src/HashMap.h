#ifndef DUNGEONGAME_HASHMAP_H
#define DUNGEONGAME_HASHMAP_H

#include "iostream"

using namespace std;

template<class K, class V>
class MapNode {

public:
    MapNode(K &key, V &value) {
        first = key;
        second = value;
    }

    K first;
    V second;

    void print() {
        cout << "{\"";
        cout << first;
        cout << "\"";
        cout << ": \"";
        cout << second;
        cout << "\"}\n";
    }

    MapNode() {}

    void setValue(V value) {
        second = value;
    }
};

template<class K, class V>
class HashMap {
    MapNode<K, V> *array;

    int _capacity;
    int _size;

    void sort() {
        for (int i = 1; i < size(); i++) {
            for (int j = i; j > 0 && array[j - 1].first > array[j].first; j--) {
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

    void insert(K key, V value) {
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

    class iterator {
    public:
        typedef iterator self_type;
        typedef MapNode<K, V> &reference;
        typedef MapNode<K, V> *pointer;

        iterator(pointer ptr) : ptr_(ptr) {}

        self_type operator++() { ptr_++; return *this; }
        self_type operator++(int j) { self_type i = *this; ptr_++; return i; }

        reference operator*() { return *ptr_; }

        pointer operator->() { return ptr_; }

        bool operator==(const self_type &rhs) const{ return ptr_ == rhs.ptr_; }

        bool operator!=(const self_type &rhs) const { return ptr_ != rhs.ptr_; }

    private:
        pointer ptr_;
    };

    class const_iterator {
    public:
        typedef const_iterator self_type;
        typedef MapNode<K, V> value_type;
        typedef MapNode<K, V> &reference;
        typedef MapNode<K, V> *pointer;

        const_iterator(pointer ptr) : ptr_(ptr) {}

        self_type operator++() { ptr_++; return *this; }
        self_type operator++(int j) { self_type i = *this; ptr_++; return i; }

        const reference operator*() { return *ptr_; }
        const value_type* operator->() { return ptr_; }

        bool operator==(const self_type &rhs) const{ return ptr_ == rhs.ptr_; }

        bool operator!=(const self_type &rhs) const { return ptr_ != rhs.ptr_; }

    private:
        pointer ptr_;
    };

    iterator begin() {
        return iterator(array);
    }

    iterator end() {
        return iterator(array + _size);
    }

    const_iterator begin() const {
        return const_iterator(array);
    }

    const_iterator end() const {
        return const_iterator(array + _size);
    }

    V &operator[](K key) {
        int index;
        if (contains(key, index)) {
            return array[index].second;
        }
    }

    V operator[](K key) const {
        int index;
        if (contains(key, index)) {
            return array[index].second;
        }
    }

    bool contains(K key, int &index) {
        int l = 0, r = size(), mid;

        while (l < r) {
            mid = (l + r) / 2;
            if (array[mid].first > key) r = mid;
            else l = mid + 1;
        }
        r--;

        if (array[r].first == key) {
            index = r;
            return true;
        }
    }

    bool contains(K key) {
        int l = 0, r = size(), mid;

        while (l < r) {
            mid = (l + r) / 2;
            if (array[mid].first > key) r = mid;
            else l = mid + 1;
        }
        r--;

        if (array[r].first == key) {
            return true;
        }
    }

    int size() { return _size; }
};

#endif
