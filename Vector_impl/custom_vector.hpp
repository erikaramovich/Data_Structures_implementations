#include <iostream>
#include <random>
#include <initializer_list>

template <class T>
class Vector {
public:
	Vector(std::size_t arr_size = 0);

	Vector(const std::initializer_list <T>& list);

	Vector(const Vector& other);

	Vector& operator=(const Vector& other);

	~Vector(); 

	std::size_t size() const;

	bool empty() const;

	std::size_t capacity() const; 

	T operator[](std::size_t index) const;

	T& operator[](std::size_t index);
    
	void resize(std::size_t new_capacity);

	void push_back(const T& x);

	T pop_back();

	void clear();

	void insert(size_t pos, T value);

	T erase(size_t pos);

	bool operator==(const Vector& arg);

	void print();

	void size_cap_info();

private:
	std::size_t arr_size;
	std::size_t arr_capacity;
	T* arr;
};

template <class T>
Vector<T>::Vector(std::size_t arr_size): 
    arr_size(arr_size),
    arr_capacity(arr_size * 2 + 1),
    arr(new T[arr_capacity]{})
{}

template <class T>
Vector<T>::Vector(const std::initializer_list <T>& list):Vector(list.size())
{
    int i = 0;
    for (auto& elem : list)
    {
        arr[i] = elem;
        ++i;
    }
    std::cout << "Constructor with std::initializer_list parametr\n";
}

template <class T>
Vector<T>::Vector(const Vector& other):
    arr_size(other.arr_size),
    arr_capacity(other.arr_capacity),
    arr(new T[arr_capacity]{})
{
    for (std::size_t i = 0; i < arr_size; i++)
    {
        arr[i] = other.arr[i];
    }
    std::cout << "Deep Copy Constructor\n";
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    arr_size = other.arr_size;
    arr_capacity = other.arr_capacity;
    T* array = new T[arr_capacity]{};
    for (std::size_t i = 0; i < arr_size; i++)
    {
        array[i] = other.arr[i];
    }
    delete[] arr;
    arr = array;
    std::cout << "Operator = Overloaded" << "\n";
    return *this;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] arr;
}

template <class T>
std::size_t Vector<T>::size() const
{
    return arr_size;
}

template <class T>
bool Vector<T>::empty() const
{
    return arr_size == 0;
}

template <class T>
std::size_t Vector<T>::capacity() const
{
    return arr_capacity;
}

template <class T>
T Vector<T>::operator[](std::size_t index) const
{
    if (index >= arr_size)
    {
        throw std::runtime_error("Your index is invalid");
    }
    return arr[index];
}

template <class T>
T& Vector<T>::operator[](std::size_t index)
{
    if (index >= arr_size)
    {
        throw std::runtime_error("Your index is invalid");
    }
    return arr[index];
}

template <class T>
void Vector<T>::resize(std::size_t new_capacity)
{
    if (new_capacity < 0)
    {
        throw std::runtime_error("Capacity can't be negative!");
    }

    arr_capacity = new_capacity;
    if (arr_capacity <  arr_size)
    {
        arr_size = arr_capacity;
    }

    T* new_arr = new T[arr_capacity]{};
    for (std::size_t i = 0; i < arr_size; i++)
    {
        new_arr[i] = arr[i];
    }

    delete[]arr;
    arr = new_arr;
}

template <class T>
void Vector<T>::push_back(const T& x)
{
    if (arr_size == arr_capacity)
    {
        resize(arr_size*2 + 1); 
    }
    
    arr[arr_size] = x;
    arr_size++;
}

template <class T>
T Vector<T>::pop_back()
{
    if (arr_size == 0)
    {
        throw std::runtime_error("Your vector is empty.Nothing to pop_back!");
    }
    T x = arr[arr_size - 1];
    --arr_size;
    return x;
}

template <class T>
void Vector<T>::clear()
{
    arr_size = 0;
}

template <class T>
void Vector<T>::insert(size_t pos, T value)
{
    if (pos >= arr_size)
    {
        throw std::runtime_error("Your index is invalid");
    }

    push_back(value);
    for (size_t i = arr_size - 1; i != pos; i--)
    {
        std::swap(arr[i], arr[i - 1]);
    }
}

template <class T>
T Vector<T>::erase(size_t pos)
{
    if (pos >= arr_size)
    {
        throw std::runtime_error("Your index is invalid");
    }
    T ret = arr[pos];

    for (size_t i = pos + 1; i < arr_size; i++)
    {
        std::swap(arr[i], arr[i - 1]);
    }
    arr_size--;

    return ret;
}

template <class T>
bool Vector<T>::operator==(const Vector& arg)
{
    if (arr_size != arg.arr_size)
    {
        return false;
    }
    for (std::size_t i = 0; i < arr_size; i++)
    {
        if (arr[i] != arg.arr[i])
        {
            return false;
        }
    }
    return true;
}

template <class T>
void Vector<T>::print()
{
    for (size_t i = 0; i < arr_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
void Vector<T>::size_cap_info()
{
    std::cout << "Size: " << arr_size << " , " << "Capacity: " << arr_capacity << std::endl;
}


