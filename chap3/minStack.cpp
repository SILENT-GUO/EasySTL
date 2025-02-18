//
// Created by Zebin Guo on 1/1/25.
//
#include <Stack.hpp>
// use single linked list as a base class
template <typename T>
class MinStack {
// the key is to maintain a auxiliaryStack, capable of recording the min element by:
// 1. when pop, if the current element is the top element of auxiliaryStack (the current min element), we pop it in auxiliaryStack.
// 2. when push, if the current element is smaller than the top element of auxiliaryStack, we push it to auxiliaryStack.
private:
    Stack<T> mainStack;
    Stack<T> auxiliaryStack;
public:
    // use default constructor.
    MinStack() = default;
    ~MinStack() {
        while (!mainStack.isEmpty()) {
            mainStack.pop();
        }
        while (!auxiliaryStack.isEmpty()) {
            auxiliaryStack.pop();
        }
    }
    void pop() {
        if (mainStack.top() == auxiliaryStack.top()) {
            auxiliaryStack.pop();
        }
        mainStack.pop();
    }

    const T& top() const {
        return mainStack.top();
    }
    // push to the top of stack
    void push(const T& data) {
        mainStack.push(data);
        if (auxiliaryStack.isEmpty() || data < auxiliaryStack.top()) {
            auxiliaryStack.push(data);
        }
    }

    [[nodiscard]] bool isEmpty() const {
        return mainStack.isEmpty();
    }

    const T& minElement() const {
        return auxiliaryStack.top();
    }

};
