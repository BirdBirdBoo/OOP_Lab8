#include "array.h"

void Array::print() const
{
    cout << "Array of size " << getLength() << endl;
    printData();
}

void Array::printData() const
{
    cout << "Data: [";

    if (getLength() > 0) {
        for (size_t i = 0; i < getLength() - 1; ++i) {
            cout << (*this)[i] << ", ";
        }
        cout << (*this)[getLength() - 1];
    }
    cout << "]" << endl;
}

void Array::checkBounds(size_t index) const {
    if (index < 0 || index >= getLength()) {
        throw new std::invalid_argument("Array index is out of bounds!");
    }
}

IncrementalArray::IncrementalArray() : IncrementalArray(DEFAULT_INITIAL_SIZE)
{
}

IncrementalArray::IncrementalArray(size_t initialSize)
{
    if (initialSize == 0)
        return;

    alloc(initialSize);
}

IncrementalArray::~IncrementalArray()
{
    free(data);
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
    if (data == nullptr) {
        data = (int *) calloc(expectedCapacity, sizeof (int));
    } else {
        data = (int *) realloc(data, expectedCapacity * sizeof (int));
    }
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

    data[length] = newElement;
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

void IncrementalArray::print() const
{
    cout << "IncrementalArray of length " << length << " (capacity: " << capacity << ")" << endl;
    printData();
}
