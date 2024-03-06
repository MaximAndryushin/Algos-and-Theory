#include <queue>


template<typename T, typename _Compare = std::less<T>>
struct EPQ {
    void push(T val) {
        ins.push(val);
    }

    const T& top() {
        while(!rem.empty() && ins.top() == rem.top()) {
            ins.pop();
            rem.pop();
        }
        return ins.top();
    }

    void pop() {
        while(!rem.empty() && ins.top() == rem.top()) {
            ins.pop();
            rem.pop();
        }
        ins.pop();
    }

    void erase(T v) {
        rem.push(v);
    } 

    std::size_t size() {
        return ins.size() - rem.size();
    }

    bool empty() {
        return size() == 0;
    }
    
private:
    std::priority_queue<T, vector<T>, _Compare> ins, rem;
};
