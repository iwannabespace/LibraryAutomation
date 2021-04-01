#include "Vector.hpp"

template<class T> 
Vector<T>::Vector()
    :capacity(5), size(0)
{
    elems = new T[capacity];
}

template<class T>
Vector<T>::Vector(std::size_t capacity)
    :capacity(capacity), size(0)
{
    elems = new T[capacity];
}

template<class T>
Vector<T>::Vector(const Vector<T>& vec)
    :capacity(vec.Capacity()), size(vec.Size())
{
    elems = new T[capacity];
    for (std::size_t i = 0; i < vec.Size(); i++)
        elems[i] = vec[i];
}

template<class T>
Vector<T>::Vector(std::initializer_list<T> init_list)
    :capacity(init_list.size() + 5), size(init_list.size())
{
    int pos = 0;
    elems = new T[capacity];
    for (const T& elem: init_list)
        elems[pos++] = elem;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] elems;
}

template<class T>
std::size_t Vector<T>::Size() const
{
    return size;
}

template<class T>
std::size_t Vector<T>::Capacity() const
{
    return capacity;
}

template<class T>
T& Vector<T>::Get(std::size_t pos) const
{
    if (pos >= size || pos < 0)
        throw std::string("Index out of bounds!");

    else return elems[pos];
}

template<class T>
T& Vector<T>::operator[](std::size_t pos) const
{
    if (pos >= size || pos < 0)
        throw std::string("Index out of bounds!");
    
    else return elems[pos];
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& vec) const
{
    //Vector<T> temp = this; // or ... = *this ?

    Vector<T> temp(capacity);
    for (std::size_t i = 0; i < size; i++)
        temp.Push(elems[i]);

    for (std::size_t i = 0; i < vec.Size(); i++)
        temp.Push(vec[i]);
    
    return temp;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& vec) const
{
    for (std::size_t i = 0; i < vec.Size(); i++)
        if (vec[i] != elems[i])
            return false;
            
    return true;
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& vec) const
{
    return !operator==(vec);
}

template<class T>
void Vector<T>::Push(const T& elem)
{
    if ((size + 1) <= capacity) 
        elems[size++] = elem;
    else
    {
        Allocate();
        elems[size++] = elem;
    }
}

template<class T>
void Vector<T>::Remove(const T& elem)
{
    int pos = 0;
    bool isAvailable = false;
    for (std::size_t i = 0; i < size; i++)
        if (elem == elems[i])
        {    
            pos = i;
            isAvailable = true;
            break;
        }
    if (isAvailable)
    {    
        T temp[size - 1];
        for (std::size_t i = 0, j = 0; j < size; i++, j++)
        {    
            if (j != pos)
                temp[i] = elems[j];
            else 
            {
                i--;
                continue;
            }
        }
        delete[] elems;
        elems = new T[--size];
        for (std::size_t i = 0; i < size; i++)
            elems[i] = temp[i];
    }
}

template<class T>
void Vector<T>::Remove_At(std::size_t pos)
{
    T temp[size - 1];
    for (std::size_t i = 0, j = 0; j < size; i++, j++)
    {    
        if (j != pos)
            temp[i] = elems[j];
        else 
        {
            i--;
            continue;
        }
    }
    delete[] elems;
    elems = new T[--size];
    for (std::size_t i = 0; i < size; i++)
        elems[i] = temp[i];
}

template<class T>
void Vector<T>::Sort() const
{
    std::sort(this->begin(), this->end());
}

template<class T>
std::vector<T> Vector<T>::ConvertTo_Std() const
{
    std::vector<T> std_v;
    for (int i = 0; i < size; i++)
        std_v.push_back(elems[i]);
    
    return std_v;
}

template<class T>
T* Vector<T>::begin() const
{
    return &elems[0];
}

template<class T>
T* Vector<T>::end() const
{
    return &elems[size];
}

template<class T>
void Vector<T>::Allocate()
{
    T temp[capacity];
    for (std::size_t i = 0; i < capacity; i++)
        temp[i] = elems[i];
    
    delete[] elems;
    elems = new T[capacity * 2];
    for (std::size_t i = 0; i < capacity; i++)
        elems[i] = temp[i];
    
    capacity *= 2;
}

template<class U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& vec)
{
    os << "{ ";
    for (std::size_t i = 0; i < vec.Size(); i++)
    {
        os << vec[i];
        if (i < vec.Size() - 1)
            os << ", ";
    }
    os << " }";
    return os;
}

template<class U>
std::ostream& operator<<(std::ostream& os, const Vector<U*>& vec)
{
    os << "{ ";
    for (std::size_t i = 0; i < vec.Size(); i++)
    {
        os << *vec[i];
        if (i < vec.Size() - 1)
            os << ", ";
    }
    os << " }";
    return os;
}