#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

// implement a Vector class (not thread-safe)
template <typename T>
class Vector {
private:
    T* dataPointer;
    size_t numElements; // current number of elements in array
    size_t numAllocatedSpace; // Total allocated numAllocatedSpace
    void grow(){
        T* newDataPointer = new T[numAllocatedSpace * 2];
        for(size_t i = 0; i < numElements; i++){
            newDataPointer[i] = dataPointer[i];
            dataPointer[i].~T(); // 析构
        }
        numAllocatedSpace *= 2;
        delete [] dataPointer;
        dataPointer = newDataPointer;
    }
public:
    Vector(): numElements(0), numAllocatedSpace(1){ // by default, it should add by twice.
        dataPointer = new T[1];
    }
    explicit Vector(const size_t initialCapacity): numElements(0), numAllocatedSpace(initialCapacity){ // by default, it should add by twice.
        dataPointer = new T[numAllocatedSpace];
    }
    // initializer_list is a lightweight wrapper supporting iterative search.
    Vector(std::initializer_list<T> list): numElements(list.size()), numAllocatedSpace(list.size()){
      dataPointer = new T[numAllocatedSpace];
      std::copy(list.begin(), list.end(), dataPointer);
    }
    ~Vector(){
        delete [] dataPointer;
    }

    void resize(const size_t newSize) {
        if (newSize == numElements) { // do nothing;
            return;
        }
        if (newSize < numElements) {
            for (size_t i = newSize; i < numElements; i++) {
                dataPointer[i].~T();
            }
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
            dataPointer[i].~T();
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

    T& operator[](size_t index){
        if(index >= numElements){
            throw std::out_of_range("Index out of bounds");
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

    T* begin(){
      return dataPointer;
    }
    T* end(){
      return dataPointer + numElements;
    }
};

#endif