//
// Created by Zebin Guo on 1/1/25.
//
#include <Stack.hpp>
template<class T>
class SortedStack {
    // 这个是使用大顶堆和小顶堆组成有序的堆
    // 我们要求大顶堆的所有元素都小于小顶堆（即大顶堆顶小于小顶堆顶），那么我们取pop的时候只需要把大顶堆的元素都pour到小顶堆即可
    // 如下是条件：
    // 小顶堆为核心，在pop或者取top的时候都需要把大顶堆所有元素pour到小顶堆上
    // 如果当前插入元素 为 a, 大顶堆顶为 b 小顶堆顶为 c，我们有 b < c.
    // 好条件：如果 b < a < c,那么我们只需要把a push进小顶堆顶，即让c = a
    // 如果 a < b < c, 那么我们一直把大顶堆顶的元素push到小顶堆，直到满足好条件
    // 相似的，如果 b < c < a, 那么我们一直把小顶堆顶的元素push到大顶堆，直到满足好条件
private:
    Stack<T> maxStack, minStack;
public:
    SortedStack() = default;
    ~SortedStack() {
        while (!maxStack.empty()) {
            maxStack.pop();
        }
        while (!minStack.empty()) {
            minStack.pop();
        }
    }

    void pop() {
        while (!maxStack.empty()) {
            minStack.push(maxStack.top());
            maxStack.pop();
        }
        minStack.pop();
    }

    void push(T value) {
        if (maxStack.empty() || (value <= minStack.top() && value >= maxStack.top())) {
            minStack.push(value);
        }else if (value > minStack.top()) {
            while (!minStack.empty() && value > minStack.top()) {
                maxStack.push(minStack.top());
                minStack.pop();
            }
            minStack.push(value);
        }else if (value < maxStack.top()) {
            while (!maxStack.empty() && value < maxStack.top()) {
                minStack.push(maxStack.top());
                maxStack.pop();
            }
            maxStack.push(value);
        }
    }

    const T& top() {
        while (!maxStack.empty()) {
            minStack.push(maxStack.top());
            maxStack.pop();
        }
        return minStack.top();
    }

    [[nodiscard]] bool empty() {
        return minStack.empty() && maxStack.empty();
    }

};