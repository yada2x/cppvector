#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

const int DEFAULT_VECTOR_SIZE = 10;

// TO DO: unit tests, fast access methods, move semantics, error handling

template <typename T>
class VectorIterator {
    public:
        using ValueType = T;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        VectorIterator(PointerType ptr): m_ptr(ptr) {};

        VectorIterator& operator++() {
            m_ptr++;
            return *this;
        }

        VectorIterator operator++(int) {
            VectorIterator tmp = *this;
            ++m_ptr;
            return tmp;
        }

        VectorIterator& operator--() {
            m_ptr--;
            return *this;
        }

        VectorIterator operator--(int) {
            VectorIterator tmp = *this;
            --m_ptr;
            return tmp;
        }

        ReferenceType operator[](int idx) {
            return *(m_ptr + idx);
        }

        PointerType operator->() { return m_ptr; }

        ReferenceType operator*() { return *m_ptr; }

        bool operator==(const VectorIterator& other) const {
            return m_ptr = other.m_ptr;
        }

        bool operator!=(const VectorIterator& other) const {
            return m_ptr != other.m_ptr;
        }

    private:
        PointerType m_ptr;
};

template <typename T>
class Vector {
    public:
        using ValueType = T; // the STL does this
        using Iterator = VectorIterator<T>;

        Vector() {
            size = 0;
            capacity = DEFAULT_VECTOR_SIZE;
            elems = new T[DEFAULT_VECTOR_SIZE];
        }
        
        Vector(int n, const T& init) {
            size = n;
            capacity = n * 2;
            elems = new T[capacity];
            for (int i = 0; i < size; i++) {
                elems[i] = init;
            }
        } 

        Vector(const Vector& other) {
            size = other.size;
            capacity = other.capacity;
            elems = new T[capacity];
            for (int i = 0; i < size; i++) {
                elems[i] = other.elems[i];
            }
        }

        ~Vector() { delete[] elems; }

        int Size() const { return size; }
        int Capacity() const { return capacity;}
        bool IsEmpty() const {return size == 0;}

        void Push_back(const T& obj) {
            if (size == capacity) {
                resize();
            }
            elems[size] = obj;
            size++;
        }

        void Pop_back() {
            if (size > 0) {
                size--;
            }
        }

        void Erase(int idx) {
            for (int i = idx; i < size - 1; ++i) {
                elems[i] = elems[i + 1];
            }
            size--;
        }

        void Insert(int idx, const T& value) {
            if (size == capacity) {
                resize();
            }
            size++;
            for (int i = size; i >= idx; --i) {
                elems[i] = elems[i - 1];
            }
            elems[idx] = value;
        }

        void Clear() { size = 0; }
       
        // modifying v[i] = x
        T& operator[](int idx) {
            if (idx < 0 || idx >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return elems[idx];
        }

        // read only x = v[i]
        const T& operator[](int idx) const {
            if (idx < 0 || idx >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return elems[idx];
        }

        Vector& operator=(const Vector& other) {
            if (this == &other) {
                return *this;
            }
            
            if (other.size > size) {
                delete[] elems;
                capacity = other.capacity;
                elems = new T[capacity];
            }

            for (int i = 0; i < other.size; ++i) {
                elems[i] = other[i];
            }
            size = other.size;
            return *this;
        }

        Iterator begin() {
            return VectorIterator(elems);
        }

        Iterator end() {
            return VectorIterator(elems + size);
        }

        Iterator rbegin() {
            return VectorIterator(elems + size - 1);
        }

        Iterator rend() {
            return VectorIterator(elems - 1);
        }

    private:
        int size;
        int capacity;
        T* elems;

        void resize() {
            capacity *= 2;
            T* temp = new T[capacity];

            for (int i = 0; i < size; i++) {
                temp[i] = elems[i];
            }

            delete[] elems;
            elems = temp;
        };
};

#endif
