//
// Created by Zebin Guo on 1/1/25.
//
#include <Stack.hpp>

// this class uses a input stack and a output stack to build the queue
// every time a new element is inserted in the input stack
// when we ask the top element, we do:
// 1. if output stack is empty, we pour all element in input stack into output stack (note this operation reverts the order of elements!)
// 2. if the output stack is non-empty, return the top element of output stack
template<class T>
class TwoStackQueue {
private:
    Stack<T> inputStack, outputStack;
    size_t numElements = 0;
public:
    TwoStackQueue() = default;
    ~TwoStackQueue() {
        while (!inputStack.isEmpty()) inputStack.pop();
        while (!outputStack.isEmpty()) outputStack.pop();
    }

    [[nodiscard]] bool empty() const {
        return inputStack.isEmpty() && outputStack.isEmpty();
    }

    [[nodiscard]] size_t size() const {
        return numElements;
    }

    const T& front() {
        if (numElements == 0) {throw std::out_of_range("Front: The queue is empty.");}
        if (outputStack.isEmpty()) {
            while (!inputStack.isEmpty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        return outputStack.top();
    }

    const T& back() {
        if (numElements == 0) {throw std::out_of_range("back: The queue is empty.");}
        if (!inputStack.isEmpty()) return inputStack.top();
        while (!outputStack.isEmpty()) {
            inputStack.push(outputStack.top());
            outputStack.pop();
        }
        return inputStack.top();
        // here we may change the status of two stacks
    }

    void push(const T& element) {
        inputStack.push(element);
        numElements++;
    }

    void pop() {
        if (numElements == 0) {
            throw std::out_of_range("pop: The queue is empty.");
        }
        if (outputStack.isEmpty()) {
            while (!inputStack.isEmpty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        outputStack.pop(); // Remove the front element
        numElements--;
    }
};