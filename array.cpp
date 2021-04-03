#include "array.h"

void Array::checkBounds(size_t index) const {
    if (index < 0 || index >= getLength()) {
        throw new std::invalid_argument("Array index is out of bounds!");
    }
}

int IncrementalArray::operator[](size_t index) const {
    checkBounds(index);

    return data[index];
}


int &IncrementalArray::operator[](size_t index) {
    checkBounds(index);

    return data[index];
}

void IncrementalArray::alloc(size_t expectedCapacity)
{
    data = (int *) realloc(data, expectedCapacity);
    capacity = expectedCapacity;
}

size_t IncrementalArray::getLength() const
{
    return length;
}

void IncrementalArray::add(int newElement) {
    if (length + 1 >= capacity) {
        alloc(length + 1);
    }

    data[length - 1] = newElement;
    ++length;
}

void IncrementalArray::addAll(const Array &other)
{
    const size_t newLength = length + other.getLength();
    if (newLength >= capacity) {
        alloc(newLength);
    }

    for (size_t i = length; i < newLength; ++i) {
        data[i] = other[i - length];
    }
    length = newLength;
}

