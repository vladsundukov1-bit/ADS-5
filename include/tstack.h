// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
    private:
    static const int k = size;
    T data[k];
    int top_index;

    public:
    TStack() : top_index(-1) {}
    void push(T value) {
        if (top_index < k - 1) {
            data[++top_index] = value;
        }
    }

    T pop() {
        if (top_index >= 0) {
            return data[top_index--];
        }
        return T();
    }

    T top() {
        if (top_index >= 0) {
            return data[top_index];
        }
        return T();
    }

    bool is_empty() {
        return top_index == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
