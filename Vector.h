#ifndef VECTOR_H
#define VECTOR_H

const int DEFAULT_VECTOR_SIZE = 10;

// TO DO: iterators, unit tests, fast access methods, move semantics, error handling

template <typename T>
class Vector {
    private:
        int size;
        int capacity;
        T* elems;

    public:
        Vector();
        Vector(int n, const T& init); // constructor with predefined size and initial values
        Vector(const Vector& other); // copy constructor

        ~Vector();

        int Size() const ;
        int Capacity() const;
        bool IsEmpty() const;

        void Push_back(const T& obj);
        void Pop_back();
        void Erase(int idx);
        void Insert(int idx, const T& value);
        void Clear();
       
        T& operator[](int idx); // modifying v[i] = x
        const T& operator[](int index) const; // read only x = v[i]
        Vector& operator=(const Vector& other);

};

template <typename T>
Vector<T>::Vector() {
    size = 0;
    capacity = DEFAULT_VECTOR_SIZE;
    elems = new T[DEFAULT_VECTOR_SIZE];
}

template <typename T>
Vector<T>::Vector(int n, const T& init) {
    size = n;
    capacity = n * 2;
    elems = new T[capacity];
    for (int i = 0; i < size; i++) {
        elems[i] = init;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    elems = new T[capacity];
    for (int i = 0; i < size; i++) {
        elems[i] = other.elems[i];
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] elems;
}

template <typename T>
int Vector<T>::Size() const { return size; }

template <typename T>
int Vector<T>::Capacity() const { return capacity; }

template <typename T>
bool Vector<T>::IsEmpty() const { return size == 0; }

template<typename T> 
void Vector<T>::Push_back(const T& obj) {
    if (size == capacity) {
        capacity *= 2;
        T* temp = new T[capacity];

        for (int i = 0; i < size; i++) {
            temp[i] = elems[i];
        }

        delete[] elems;
        elems = temp;
    }
    elems[size] = obj;
    size++;
}

template <typename T>
void Vector<T>::Pop_back() {
    if (size > 0) {
        size--;
    }
}

template <typename T>
void Vector<T>::Erase(int idx) {
    for (int i = idx; i < size - 1; ++i) {
        elems[i] = elems[i + 1];
    }
    size--;
}

template <typename T>
void Vector<T>::Insert(int idx, const T& value) {
    // TO DO: A CAPACITY AND SIZE CHECK!
    size++;
    for (int i = size; i >= idx; --i) {
        elems[i] = elems[i - 1];
    }
    elems[idx] = value;
}

template <typename T>
void Vector<T>::Clear() {
    size = 0;
}

template <typename T>
T& Vector<T>::operator[](int idx) {
    // NEED TO DO BOUNDS CHECK
    return elems[idx];
}

template <typename T>
const T& Vector<T>::operator[](int idx) const {
    // NEED TO DO BOUNDS CHECK
    return elems[idx];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {

    // PREVENT SELF ASSIGNMENT
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

#endif
