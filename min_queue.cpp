#include <stack>
#include <utility>

using namespace std;

template <typename T, typename Comp = less<T>>
struct Queue {
    Queue(const Comp& cmp = Comp{}) : cmp(cmp) {};

    void push(const T& val) {
        push(val, st1);
    }

    T best() const {
        if (!st1.empty() && !st2.empty()) {
            return op(st1.top().second, st2.top().second);
        } else if (!st1.empty()) {
            return st1.top().second;
        } else if (!st2.empty()) {
            return st2.top().second;
        } else {
            assert(true);
        }
    }

    void pop() {
        if (st2.empty()) {
            while(!st1.empty()) {
                auto [val, _] = st1.top();
                push(val, st2);
                st1.pop();
            }
        }
        st2.pop();
    }

private:
    void push(const T& val, stack<pair<T, T>>& st) {
        if (!st.empty())
            st.emplace(val, op(val, st.top().second));
        else 
            st.emplace(val, val);
    }

    T op(const T& a, const T& b) const {
        return cmp(a, b) ? a : b;
    }

    const Comp cmp;

    stack<pair<T, T>> st1, st2;
};