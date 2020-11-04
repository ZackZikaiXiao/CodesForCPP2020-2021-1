#include "MyVector.h"

int main() {
    std::cout << "Hello, Test7.3!" << std::endl;
    int inputV[3] = {1, 2, 3};
    MyVector<int> v0;       // 默认构造
    MyVector<int> v1(inputV, 3);     // 带参构造
    MyVector<int> v2(v1);      // 复制构造
    MyVector<int> v3 = v2;  // 赋值
    cout << "v3 size:\t" << v3.size();
}
