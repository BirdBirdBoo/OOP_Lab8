#include "array.h"

// BEGIN ARRAY

void Array::add(int newElement) {
    ensureCapacity(length + 1);
    setElementAtSafe(length, newElement);
    ++length;
}

void Array::addAll(const Array &other) {
    const size_t newLength = length + other.length;
    ensureCapacity(newLength);

    for (size_t i = length; i < newLength; ++i) {
        setElementAtSafe(i, other[i - length]);
    }
    length = newLength;
}

void Array::addAll(const int *nativeArray, size_t arraySize) {
    const size_t newLength = length + arraySize;
    ensureCapacity(newLength);

    for (size_t i = arraySize; i < newLength; ++i) {
        setElementAtSafe(i, nativeArray[i - length]);
    }

    length = newLength;
}

void Array::print() const {
    cout << "Array of size " << getLength() << endl;
    printData();
}

Array &Array::operator+=(int element) {
    this->add(element);
    return *this;
}

Array &Array::operator+=(const Array& other) {
    this->addAll(other);
    return *this;
}

void Array::printData() const {
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

std::ostream &operator<<(std::ostream &output, const Array &toWrite) {
    output << "Array[";
    const size_t len = toWrite.getLength();

    if (len != 0) {
        output << toWrite[0];
        for (size_t i = 1; i < len; ++i) {
            output << "," << toWrite[i];
        }
    }
    output << ']' << endl;
    return output;
}

std::istream &operator>>(std::istream &input, Array &toRead) {
    toRead.clear();

    std::string line;
    getline(input, line);

    size_t startPos = line.find("Array[");

    if (startPos == std::string::npos)
        return input;

    line = line.substr(startPos);

    size_t endPos = line.find_first_of(']');
    if (endPos == std::string::npos)
        return input;

    if (endPos - startPos == 1)
        return input;

    size_t previousDelimeter = startPos + 5;
    size_t currentDelimeter = line.find_first_of(',');

    while (currentDelimeter != std::string::npos && currentDelimeter < endPos) {
        int element = std::stoi(line.substr(previousDelimeter + 1, currentDelimeter));
        toRead.add(element);

        previousDelimeter = currentDelimeter;
        currentDelimeter = line.find_first_of(',', currentDelimeter + 1);
    }

    if (currentDelimeter == std::string::npos && previousDelimeter != startPos + 5) {
        int element = std::stoi(line.substr(previousDelimeter + 1, endPos));
        toRead.add(element);
    }

    return input;
}

// END ARRAY



// BEGIN INCREMENTAL ARRAY

IncrementalArray::IncrementalArray() : IncrementalArray(DEFAULT_INITIAL_SIZE)  {
}

IncrementalArray::IncrementalArray(size_t initialSize) {
    if (initialSize == 0)
        return;

    alloc(initialSize);
}

IncrementalArray::~IncrementalArray() {
    if (data == nullptr)
        return;

    free(data);
}

int IncrementalArray::operator[](size_t index) const {
    checkBounds(index);

    return data[index];
}

void IncrementalArray::clear()
{
    length = 0;
}

int &IncrementalArray::operator[](size_t index) {
    checkBounds(index);

    return data[index];
}

void IncrementalArray::alloc(size_t expectedCapacity) {
    if (data == nullptr) {
        data = (int *) calloc(expectedCapacity, sizeof (int));
    } else {
        data = (int *) realloc(data, expectedCapacity * sizeof (int));
    }
    capacity = expectedCapacity;
}

void IncrementalArray::ensureCapacity(size_t requiredCapacity) {
    if (requiredCapacity > capacity) {
        alloc(requiredCapacity);
    }
}

void IncrementalArray::print() const {
    cout << "IncrementalArray of length " << length << " (capacity: " << capacity << ")" << endl;
    printData();
}

void IncrementalArray::setElementAtSafe(size_t index, int element) {
    data[index] = element;
}

// END INCREMENTAL ARRAY



// BEGIN BLOCKY ARRAY

BlockyArray::BlockyArray(): BlockyArray(DEFAULT_INITIAL_BLOCK_SIZE) {
}

BlockyArray::BlockyArray(size_t initialBlockSize):
    currentBlockSize(initialBlockSize) {
    if (initialBlockSize == 0) {
        return;
    }

    alloc(initialBlockSize);
}

BlockyArray::~BlockyArray() {
    if (data == nullptr)
        return;

    free(data);
}

void BlockyArray::alloc(size_t expectedCapacity) {
    size_t tempCapacity = capacity;
    while (tempCapacity < expectedCapacity) {
        tempCapacity += currentBlockSize;

        incrementBlockSize();
    }

    if (data == nullptr) {
        data = (int *) calloc(tempCapacity, sizeof (int));
    } else {
        data = (int *) realloc(data, tempCapacity * sizeof (int));
    }

    capacity = tempCapacity;
}

void BlockyArray::ensureCapacity(size_t expectedCapacity) {
    if (expectedCapacity > capacity) {
        alloc(expectedCapacity);
    }
}

void BlockyArray::incrementBlockSize() {
    currentBlockSize += blockSizeIncrement;
}

int BlockyArray::operator[](size_t index) const {
    checkBounds(index);

    return data[index];
}

void BlockyArray::clear()
{
    length = 0;
}

int &BlockyArray::operator[](size_t index) {
    checkBounds(index);

    return data[index];
}

void BlockyArray::setElementAtSafe(size_t index, int element) {
    data[index] = element;
}

void BlockyArray::print() const {
    cout << "BlockyArray of length " << length
         << " (capacity: " << capacity << "; next block size: " << currentBlockSize << ")"
         << endl;
    printData();
}
