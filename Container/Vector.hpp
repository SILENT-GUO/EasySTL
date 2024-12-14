#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <initializer_list>

template <typename T>
class Vector {
protected: // Changed to protected for derived class access
    T* dataPointer;
    size_t numElements; // current number of elements in array
    size_t numAllocatedSpace; // Total allocated numAllocatedSpace

    void grow(){
        size_t newCapacity = numAllocatedSpace * 2;
        T* newDataPointer = new T[newCapacity];
        for(size_t i = 0; i < numElements; i++){
            newDataPointer[i] = dataPointer[i];
        }
        numAllocatedSpace = newCapacity;
        delete [] dataPointer;
        dataPointer = newDataPointer;
    }

public:
    // Default Constructor
    Vector(): numElements(0), numAllocatedSpace(1){
        dataPointer = new T[numAllocatedSpace];
    }

    // Constructor with initial capacity
    explicit Vector(const size_t initialCapacity): numElements(0), numAllocatedSpace(initialCapacity){
        dataPointer = new T[numAllocatedSpace];
    }

    // Constructor with initial size and value
    Vector(const size_t initialSize, const T initialValue): numElements(initialSize), numAllocatedSpace(initialSize){
        dataPointer = new T[numAllocatedSpace];
        for(size_t i = 0; i < numElements; i++) {
            dataPointer[i] = initialValue;
        }
    }

    // Constructor with initial size and value
    Vector(const size_t initialAllocatedSpace, const size_t initialNumElements,  const T initialValue): numElements(initialNumElements), numAllocatedSpace(initialAllocatedSpace){
        dataPointer = new T[numAllocatedSpace];
        for(size_t i = 0; i < numElements; i++) {
            dataPointer[i] = initialValue;
        }
    }

    // Initializer List Constructor
    Vector(std::initializer_list<T> list): numElements(list.size()), numAllocatedSpace(list.size()){
        dataPointer = new T[numAllocatedSpace];
        std::copy(list.begin(), list.end(), dataPointer);
    }

    // Copy Constructor (Deep Copy)
    Vector(const Vector& other): numElements(other.numElements), numAllocatedSpace(other.numAllocatedSpace){
        dataPointer = new T[numAllocatedSpace];
        for(size_t i = 0; i < numElements; i++) {
            dataPointer[i] = other.dataPointer[i];
        }
    }

    // Move Constructor
    Vector(Vector&& other) noexcept
        : dataPointer(other.dataPointer), numElements(other.numElements), numAllocatedSpace(other.numAllocatedSpace){
        other.dataPointer = nullptr;
        other.numElements = 0;
        other.numAllocatedSpace = 0;
    }

    // Copy Assignment Operator (Deep Copy)
    Vector& operator=(const Vector& other){
        if (this == &other) return *this;
        delete[] dataPointer;
        numElements = other.numElements;
        numAllocatedSpace = other.numAllocatedSpace;
        dataPointer = new T[numAllocatedSpace];
        for (size_t i = 0; i < numElements; i++) {
            dataPointer[i] = other.dataPointer[i];
        }
        return *this;
    }

    // Move Assignment Operator
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] dataPointer;
        dataPointer = other.dataPointer;
        numElements = other.numElements;
        numAllocatedSpace = other.numAllocatedSpace;
        other.dataPointer = nullptr;
        other.numElements = 0;
        other.numAllocatedSpace = 0;
        return *this;
    }

    // Destructor
    virtual ~Vector(){
        // std::cout << "Destructor is called" << std::endl;
        delete [] dataPointer;
        dataPointer = nullptr;
    }

    // Other member functions remain unchanged
    void resize(const size_t newSize) {
        if (newSize == numElements) { // do nothing
            return;
        }
        if (newSize < numElements) {
            numElements = newSize;
        }
        else {
            while (numAllocatedSpace < newSize) {
                grow();
            }
            if constexpr(!std::is_trivially_destructible_v<T>) {
                for (size_t i = numElements; i < newSize; i++) {
                    dataPointer[i] = T();
                }
            }
            // else primitive types are by default initialized.
            numElements = newSize;
        }
    }

    void reserve(const size_t newNumAllocatedSpace) {
        if (newNumAllocatedSpace <= numAllocatedSpace) { // do nothing
            std::cout << "Reserved space is too small!" << std::endl;
            return;
        }
        T* newDataPointer = new T[newNumAllocatedSpace];
        for(size_t i = 0; i < numElements; i++) {
            newDataPointer[i] = dataPointer[i];
        }
        numAllocatedSpace = newNumAllocatedSpace;
        delete [] dataPointer;
        dataPointer = newDataPointer;
    }

    [[nodiscard]] size_t size() const {
        return numElements;
    }

    [[nodiscard]] size_t capacity() const {
        return numAllocatedSpace;
    }

    [[nodiscard]] bool empty() const {
        return numElements == 0;
    }

    [[nodiscard]] bool full() const {
        return numElements == numAllocatedSpace;
    }

    T* data() const {
        return dataPointer;
    }

    void push_back(const T& element){
        if(numElements == numAllocatedSpace){
            //grow
            grow();
            // print a special message
            std::cout << "\033[1;32m[Vector Growth]\033[0m Capacity grown to "
                      << numAllocatedSpace << " elements!\n";
        }
        dataPointer[numElements++] = element;
    }

    void pop_back(){
        if(numElements == 0){
            throw std::out_of_range("Vector is empty");
        }
        numElements --;
    }

    bool equals(Vector<T>& other) const {
        if (numElements != other.numElements) {
            return false;
        }
        for(size_t i = 0; i < numElements; i++) {
            if (dataPointer[i] != other.dataPointer[i]) {
                return false;
            }
        }
        return true;
    }

    bool equals(Vector<const T>& other) const {
        if (numElements != other.numElements) {
            return false;
        }
        for(size_t i = 0; i < numElements; i++) {
            if (dataPointer[i] != other.dataPointer[i]) {
                return false;
            }
        }
        return true;
    }

    T& operator[](size_t index){
        if(index >= numAllocatedSpace){
            throw std::out_of_range("Index out of bounds for index: " + std::to_string(index) + " >= " + std::to_string(numElements));
        }
        return dataPointer[index];
    }

    const T& operator[](size_t index) const{
        if(index >= numElements){
            throw std::out_of_range("Index out of bounds");
        }
        return dataPointer[index];
    }

    void clear() {
        numElements = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
        os << "[";
        for(size_t i = 0; i < vector.size(); i++) {
            os << vector[i] << " ";
        }
        os << "]";
        return os;
    }

    // For non-const objects, return a writable pointer
    T* begin() {
        return dataPointer;
    }

    // For const objects, return a const pointer
    const T* begin() const {
        return dataPointer;
    }

    T* end() {
        return dataPointer + numElements;
    }

    const T* end() const{
        return dataPointer + numElements;
    }
};
#endif
