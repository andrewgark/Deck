#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

typedef unsigned int ui32;

std::default_random_engine generator;

int getRandomInt(int a, int b)
{
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

int getRandomInt()
{
    return getRandomInt(INT_MIN, INT_MAX);
}

template<typename TypeValue>
std::string convertToString(TypeValue number)
{
   std::stringstream ss;
   ss << number;
   return ss.str();
}

template <typename TypeKey>
class Deque
{
    std::ostream& os;
    ui32 memorySize;
    int left, right;
    TypeKey *array;

    void rebuild(ui32 newSize)
    {
        memorySize = newSize;
        TypeKey *newArray = new TypeKey[memorySize];
        ui32 newLeft = memorySize / 4, newRight = newLeft + right - left;
        for (ui32 i = newLeft; i <= newRight; ++i)
                newArray[i] = array[i + left - newLeft];
        left = newLeft;
        right = newRight;
        delete array;
        array = newArray;
    }

public:

    typedef TypeKey* iterator;
    typedef const TypeKey* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef const std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin()
    {
        return (array + left);
    }

    const_iterator begin() const
    {
        return (array + left);
    }

    const_iterator cbegin() const
    {
        return (array + left);
    }

    iterator end()
    {
        return (array + right + 1);
    }

    const_iterator end() const
    {
        return (array + right + 1);
    }

    const_iterator cend() const
    {
        return (array + right + 1);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(array + right + 1);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(array + right + 1);
    }

    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(array + right + 1);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(array + left);
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(array + left);
    }

    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(array + left);
    }

    bool empty() const
    {
        return right + 1 == left;
    }

    ui32 size() const
    {
        return 1 + right - left;
    }

    const TypeKey& back() const
    {
        return array[right];
    }

    TypeKey& back()
    {
        return array[right];
    }

    const TypeKey& front() const
    {
        return array[left];
    }

    TypeKey& front()
    {
        return array[left];
    }

    Deque() : memorySize(4), left(2), right(1), array(new TypeKey[2]), os(std::cout)
        {}

    void push_back(TypeKey x)
    {
        if (right + 1 >= memorySize)
            rebuild(memorySize * 2);
        ++right;
        array[right] = x;
    }

    void pop_back()
    {
        --right;
        if (memorySize >= 16 && 4 * size() <= memorySize)
            rebuild(memorySize / 2);
    }

    void push_front(TypeKey x)
    {
        if (left < 1)
            rebuild(memorySize * 2);
        --left;
        array[left] = x;
    }

    void pop_front()
    {
        ++left;
        if (memorySize >= 16 && 4 * size() <= memorySize)
            rebuild(memorySize / 2);
    }

    const TypeKey& operator[](ui32 i) const
    {
        return array[left + i];
    }

    TypeKey& operator[](ui32 i)
    {
        return array[left + i];
    }

    void print()
    {
        for (int i = 0; i < memorySize; ++i)
            if (left <= i && i <= right)
                os << array[i] << " ";
            else
                os << "# ";
        os << "\n";
    }
};
