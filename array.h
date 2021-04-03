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

    virtual void add(int newElement) = 0;
    virtual void addAll(const Array &other) = 0;

    virtual size_t getLength() const = 0;

    virtual void print() const;

    Array &operator=(const Array &other) = delete;
protected:
    void checkBounds(size_t index) const;
    void printData() const;
};

class IncrementalArray: public Array {
public:
    IncrementalArray();
    IncrementalArray(size_t initialSize);
    ~IncrementalArray();

    int operator[](size_t index) const;
    int &operator[](size_t index);

    void add(int newElement);
    void addAll(const Array &other);

    size_t getLength() const;

    void print() const;
private:
    const static size_t DEFAULT_INITIAL_SIZE = 4;

    int *data = nullptr;
    size_t length = 0;
    size_t capacity = 0;

    void alloc(size_t expectedCapacity);
};

#endif // ARRAY_H
