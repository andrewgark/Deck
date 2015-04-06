#include <iostream>
#include <string>
#include <algorithm>
typedef unsigned int ui32;

enum EDirection
{
    BACK,
    FRONT
};

template <typename TypeKey>
class Deque
{
public:
    ui32 memorySize;
    int left, right;
    TypeKey *array;

    void rebuildAfterPush(EDirection direction, TypeKey x)
    {
        memorySize *= 2;
        TypeKey *newArray = new TypeKey[memorySize];
        ui32 newLeft = memorySize / 4, newRight = newLeft + right - left;
        for (ui32 i = newLeft; i <= newRight; ++i)
                newArray[i] = array[i + left - newLeft];
        left = newLeft;
        right = newRight;
        delete array;
        array = newArray;
        if (direction == FRONT)
            array[left] = x;
        else
            array[right] = x;
    }

    void rebuildAfterPop()
    {
        memorySize /= 2;
        TypeKey *newArray = new TypeKey[memorySize];
        ui32 newLeft = memorySize / 4, newRight = memorySize * 3 / 4 - 1;
        for (ui32 i = newLeft; i <= newRight; ++i)
                newArray[i] = array[left + i - newLeft];
        left = newLeft;
        right = newRight;
        delete array;
        array = newArray;
    }

//public:

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

    Deque() : memorySize(2), left(1), right(0), array(new TypeKey[2])
        {}

    void push_back(TypeKey x)
    {
        ++right;
        if (right < memorySize)
            array[right] = x;
        else
            rebuildAfterPush(BACK, x);
    }

    void pop_back()
    {
        --right;
        if (memorySize >= 8 && 4 * size() <= memorySize)
            rebuildAfterPop();
    }

    void push_front(TypeKey x)
    {
        --left;
        if (left >= 0)
            array[left] = x;
        else
            rebuildAfterPush(FRONT, x);
    }

    void pop_front()
    {
        ++left;
        if (memorySize >= 8 && 4 * size() <= memorySize)
            rebuildAfterPop();
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
                std::cout << array[i] << " ";
            else
                std::cout << "# ";
        std::cout << "\n";
    }
};

int main()
{
    ui32 m, x, s;
    std::cin >> m;
    Deque<int> deque;
    deque.print();
    for (ui32 i = 0; i < m; ++i)
    {
        std::cin >> s;
        switch(s)
        {
            case(0):
            {
                std::cin >> x;
                deque.push_back(x);
                break;
            }

            case(1):
            {
                deque.pop_back();
                break;
            }

            case(2):
            {
                std::cin >> x;
                deque.push_front(x);
                break;
            }

            case(3):
            {
                deque.pop_front();
                break;
            }

            case(4):
            {
                std::cin >> x;
                std::cout << deque[x];
                break;
            }

            case(5):
            {
                std::sort(deque.begin(), deque.end());
                break;
            }

            case(6):
            {
                std::sort(deque.rbegin(), deque.rend());
                //for (Deque<int>::iterator i = deque.begin(); i != deque.end(); ++i)
                //    std::cout << *i << " ";
                break;
            }
        }
        deque.print();
    }
    return 0;
}
