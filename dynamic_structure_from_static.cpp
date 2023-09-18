#include <vector>
using namespace std;

template <class Internal, bool BUILD = false>
struct Wrapper {

Wrapper() : vec(1) {};

auto& get() {
    return vec.front();
}

template <typename Fn>
void apply(const Fn& f) {
    for (auto& el: vec) {
        f(el);
    }
}

void upd() {
    for (int i = 0; auto& el: vec) {
        if (el.size() > (1 << i)) {
            if (i + 1 == vec.size()) {
                vec.emplace_back();
            }
            vec[i + 1].add(move(vec[i]));
            if constexpr (BUILD) {
                vec[i + 1].build();
            }
            vec[i] = {};
        } else {
            break;
        }
    }
}

private:
    vector<Internal> vec;
};