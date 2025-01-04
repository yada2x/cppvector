#ifndef VECTOR_H
#define VECTOR_H

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
        void Insert(int idx, T value);
        void Clear();
       
        T& operator[](int idx); // modifying v[i] = x
        const T& operator[](int index) const; // read only x = v[i]
        Vector& operator=(const Vector& other);

};

#endif
