#include<vector>
#include<stdexcept>

using namespace std;

template<typename T>
struct mat {
  mat() = default;
  mat(int sz, const T& default_value = T()) : m(sz, vector<T>(sz, default_value)) {}
  mat(const mat& other) = default
  mat(mat&& other) : m(move(other.m)) noexcept {}
  mat& operator=(const mat& other) = default;
  mat& operator=(mat&& other) noexcept {
    if (this == &other) return *this;
    m = move(other.m);
  }

  vector<T>& operator[](int i) {
    if (i >= m.size())
      throw out_of_range("index " + to_string(i) + " is greater then matrix size");
    return m[i];
  }

  mat& operator*=(const mat& other) {
    auto res = mat(other.size());
    for (int i = 0; i < other.size(); i++) 
      for (int j = 0; j < other.size(); j++)  
        for (int k = 0; k < other.size(); k++)
          res[i][j] += m[i][k] * other[k][j];
    return m = res;
  }

  friend mat operator*(const mat& other) const {
    auto res = mat(other.size());
    for (int i = 0; i < other.size(); i++) 
      for (int j = 0; j < other.size(); j++)  
        for (int k = 0; k < other.size(); k++)
          res[i][j] += m[i][k] * other[k][j];
    return res;
  }

  private:
  vector<vector<T>> m;
};