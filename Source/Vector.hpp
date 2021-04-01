#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

template<class T> class Vector;
template<class U> std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);
template<class U> std::ostream& operator<<(std::ostream& os, const Vector<U*>& vec);

template<class T>
class Vector
{
    private:
        T* elems;
        int size;
        int capacity;
    public:
        Vector();
        Vector(std::size_t capacity);
        Vector(const Vector<T>& vec);
        Vector(std::initializer_list<T> init_list);
        ~Vector();
        std::size_t Size() const;
        std::size_t Capacity() const;
        T& Get(std::size_t pos) const;
        T& operator[](std::size_t pos) const;
        Vector<T> operator+(const Vector<T>& vec) const;
        bool operator==(const Vector<T>& vec) const;
        bool operator!=(const Vector<T>& vec) const;
        void Push(const T& elem);
        void Remove(const T& elem);
        void Remove_At(std::size_t pos);
        void Sort() const;
        std::vector<T> ConvertTo_Std() const;
    public:
        T* begin() const;
        T* end() const;
    public:
        template<class U> friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);
        template<class U> friend std::ostream& operator<<(std::ostream& os, const Vector<U*>& vec);
    private:
        void Allocate();
};

#include "Vector.cpp"