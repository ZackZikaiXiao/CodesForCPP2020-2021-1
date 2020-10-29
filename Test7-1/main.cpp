#include <iostream>
#include <string>
using namespace std;

template<typename T>

void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    cout << a << " " << b << endl;
}
int main()
{
    double n1, n2;
    string s1, s2;
    cout << "Please input two values:" << endl;
    cin >> n1 >> n2;
    Swap(n1, n2);
    cout << "Please input two strings:" << endl;
    cin >> s1 >> s2;
    Swap(s1, s2);
}
