#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

using std::size_t;
using std::cout;
using std::endl;

class Array
{
public:
    virtual ~Array() { };

    virtual int operator[](size_t index) const = 0;
    virtual int& operator[](size_t index) = 0;

    virtual void add(int newElement);
    virtual void addAll(const Array &other);

    virtual void ensureCapacity(size_t capacity) = 0;
    virtual size_t getLength() const {
        return length;
    }

    virtual void print() const;

    Array &operator=(const Array &other) = delete;
protected:
    virtual void setElementAtSafe(size_t index, int element) = 0;

    void checkBounds(size_t index) const;
    void printData() const;
    size_t length = 0;
};

class IncrementalArray: public Array {
public:
    IncrementalArray();
    IncrementalArray(size_t initialSize);
    ~IncrementalArray();

    int operator[](size_t index) const;
    int &operator[](size_t index);

    void ensureCapacity(size_t capacity);

    void print() const;

protected:
    void setElementAtSafe(size_t index, int element);

private:
    const static size_t DEFAULT_INITIAL_SIZE = 4;

    int *data = nullptr;
    size_t capacity = 0;

    void alloc(size_t expectedCapacity);
};

#endif // ARRAY_H
