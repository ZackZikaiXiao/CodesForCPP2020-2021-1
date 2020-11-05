#include "MyVector.h"

int main() {
    std::cout << "Hello, Test7.3!" << std::endl;
    int inputV[11] = { 3, 4, 23, 12, 34, 67, 12, 92, 113, 40, 15 };
    MyVector<int> v0;       // 默认构造
    v0.push_back(4);
    v0.push_back(5);
    v0.push_back(6);
    cout << v0.size() << endl;
    MyVector<int> v1(inputV, 11);     // 带参构造
    MyVector<int> v2(v1);      // 复制构造
    MyVector<int> v3;
    v3.insert(2, 0);
    v3 = v2;  // 赋值
    cout << v3[2] << endl;
    cout << v3.at(2) << endl;
    cout << v3.front() << endl;
    cout << v3.back() << endl;
    //while(1) cout<< v3.pop_back()<<"\t";
    cout << v3.back() << endl;
    v3.insert(2, 3);
    v3.debugshow();
    v3.erase(3);
    v3.debugshow();
    v3.sort();
    v3.debugshow();
    cout << v3.binary_search(5) << endl;
    return 0;
}
