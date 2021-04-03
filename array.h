#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>

using std::size_t;

class Array
{
public:
    virtual int operator[](size_t index) const;
    virtual int& operator[](size_t index);

    virtual void add(int newElement);
    virtual void addAll(const Array &other);

    virtual size_t getLength() const;

protected:
    void checkBounds(size_t index) const;
};

class IncrementalArray: public Array {
public:
    IncrementalArray();
    IncrementalArray(int initialSize);

    int operator[](size_t index) const;
    int &operator[](size_t index);

    void add(int newElement);
    void addAll(const Array &other);

    size_t getLength() const;
private:
    const int defaultInitialSize = 4;

    int *data = nullptr;
    size_t length = 0;
    size_t capacity = 0;

    void alloc(size_t expectedCapacity);
};

#endif // ARRAY_H
