#include <stack>
#include <stdexcept>
#include <iostream>

template <typename T>
class Advanced_Stack {
public:
    auto top() {
        
        if (!Stack.empty()) {
            return Stack.top();
        }
        
        else {
            throw std::out_of_range("Stack is empty");
        }
        

    }

    auto push(const T& element) {
        if (maximums.empty() || element >= maximums.top()) {
            maximums.push(element);
        }
        Stack.push(element);
    }

    auto pop() {
        if (!Stack.empty()) {
            if (Stack.top() == maximums.top()) {
                maximums.pop();
            }
            Stack.pop();
        }

        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    auto max() {
        if (!maximums.empty()) {
            return maximums.top();
        }

        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    auto size() {
        return Stack.size();
    }

private:
    std::stack<T> Stack;
    std::stack<T> maximums;
};

int main() {
    Advanced_Stack<int> st;

    st.push(0);
    st.push(-100);
    st.push(100);

    std::cout << "size = " << st.size() << "\n";
    std::cout << "top = " << st.top() << "   max = " << st.max() << "\n";

    st.pop();
    std::cout << "top = " << st.top() << "   max = " << st.max() << "\n";

    return 0;
}
