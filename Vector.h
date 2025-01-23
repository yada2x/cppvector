#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

constexpr int DEFAULT_VECTOR_SIZE = 10;

template <typename T>
class ConstVectorIterator {
    public:
        ConstVectorIterator(const T* ptr) : m_ptr(ptr) { }

        ConstVectorIterator& operator++() {
            m_ptr++;
            return *this;
        }

        ConstVectorIterator operator++(int) {
            ConstVectorIterator temp = *this;
            m_ptr++;
            return temp;
        }

        ConstVectorIterator& operator--() {
            m_ptr--;
            return *this;
        }

        ConstVectorIterator operator--(int) {
            ConstVectorIterator temp = *this;
            m_ptr--;
            return temp;
        }
    
        const T& operator[](int idx) const {
            return *(m_ptr + idx);
        }

        const T* operator->() const {
            return m_ptr;
        }

        const T& operator*() const {
            return *m_ptr;
        }

        bool operator==(const ConstVectorIterator& other) const {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const ConstVectorIterator& other) const {
            return m_ptr != other.m_ptr;
        }

    private:
        const T* m_ptr;
};

template <typename T>
class VectorIterator {
    public:
        using PointerType = T*;
        using ReferenceType = T&;

        VectorIterator(T* ptr): m_ptr(ptr) {};

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
            return m_ptr == other.m_ptr;
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
        using Iterator = VectorIterator<T>;
        using ConstIterator = ConstVectorIterator<T>;

        Vector(): size(0), capacity(DEFAULT_VECTOR_SIZE), elems(new T[DEFAULT_VECTOR_SIZE]) { }
        
        Vector(int n, const T& init): size(n), capacity(n * 2), elems(new T[n * 2]) {
            for (int i = 0; i < size; i++) {
                elems[i] = init;
            }
        } 

        Vector(const Vector& other): size(other.size), capacity(other.capacity), elems(new T[other.capacity]) {
            for (int i = 0; i < size; i++) {
                elems[i] = other.elems[i];
            }
        }

        // Move constructor, basically just steal the other vectors stuff
        Vector(Vector&& other) noexcept: size(other.size), capacity(other.capacity), elems(other.elems)  {
            other.size = 0;
            other.capacity = 0;
            other.elems = nullptr;
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

        //Pushback with move semantics!
        void Push_back(T&& obj) {
            if (size == capacity) {
                resize();
            }
            elems[size] = std::move(obj);
            size++;
        }

        void Pop_back() {
            if (size > 0) {
                size--;
            }
        }

        void Erase(int idx) {
            if (idx < 0 || idx >= size) {
                throw std::out_of_range("Index out of bounds");
            }

            for (int i = idx; i < size - 1; ++i) {
                elems[i] = elems[i + 1];
            }
            size--;
        }

        void Insert(int idx, const T& value) {
            if (idx < 0 || idx > size) {
                throw std::out_of_range("Index out of bounds");
            }

            if (size == capacity) {
                resize();
            }

            size++;
            for (int i = size - 1; i >= idx; --i) {
                elems[i + 1] = elems[i];
            }
            elems[idx] = value;
        }

        void Insert(int idx, T&& value) {
            if (idx < 0 || idx > size) {
                throw std::out_of_range("Index out of bounds");
            }

            if (size == capacity) {
                resize();
            }

            size++;
            for (int i = size - 1; i >= idx; --i) {
                elems[i + 1] = std::move(elems[i]);
            }
            elems[idx] = std::move(value);
        }

        void Shrink_to_fit() {
            if (size != capacity) {
                T* temp = new T[size];
            
                for (int i = 0; i < size; ++i) {
                    temp[i] = std::move(elems[i]);
                }

                delete[] elems;
                elems = temp;
                capacity = size;
            }
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

        // Modifying assignment
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

        // Move assignment
        Vector& operator=(Vector&& other) noexcept {
            if (this != &other) {
                delete[] elems;

                size = other.size;
                capacity = other.capacity;
                elems = other.elems;

                other.size = 0;
                other.capacity = 0;
                other.elems = nullptr;
            }
            return *this;   
        }

        void Print() {
            std::cout << "----------\nSize: " << size << "\nCapacity: " << capacity << "\nElements: ";
            for (int i = 0 ; i < size; ++i) {
                std::cout << elems[i] << " ";
            }
            std::cout << "----------" << std::endl;
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
