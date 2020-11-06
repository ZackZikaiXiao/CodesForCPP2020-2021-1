#include <iostream>
#include "Set.h"
#include "Complex.h"
int main() {
    {
        vector<char> temp1 = { 'a', 's', 'd' };
        vector<char> temp2 = { 's', 'd', 'f', 't' };
        Set<char> s1(temp1), s2(temp2), s3, s4;
        s1.is_elem('a');
        s1.insert('p');
        cout << "s1:\t" << s1 << endl;
        s2.erase('t');
        cout << "s2:\t" << s2 << endl;
        s3 = s1.common(s2);
        s4 = s1.sum(s2);
        cout << "s3\t" << s3 << endl;
        cout << "s4\t" << s4 << endl;
        Set<char> s5(s1);
        cout << "s5\t" << s5 << endl;
        s5 = s4;
        cout << "s5\t" << s5 << endl;
        cout << "s5 size:\t" << s5.size() << endl;
        s3.swap(s5);
        cout << "s3\t" << s3 << endl;
        cout << "s5\t" << s5 << endl;
        s3.clear();
        cout << "s3\t" << s3 << endl;
        s5.insert('a');
        cout << "Found 'a' in:\t" << s5.find('a') << endl;
    }
    {
        vector<int> temp1 = { 1, 40, 23 };
        vector<int> temp2 = { 1, 77, 129, 81, 58, 13 };
        Set<int> s1(temp1), s2(temp2), s3, s4;
        s1.is_elem(98);
        s1.insert(5);
        cout << "s1:\t" << s1 << endl;
        s2.erase(77);
        cout << "s2:\t" << s2 << endl;
        s3 = s1.common(s2);
        s4 = s1.sum(s2);
        cout << "s3\t" << s3 << endl;
        cout << "s4\t" << s4 << endl;
        Set<int> s5(s1);
        cout << "s5\t" << s5 << endl;
        s5 = s4;
        cout << "s5\t" << s5 << endl;
        cout << "s5 size:\t" << s5.size() << endl;
        s3.swap(s5);
        cout << "s3\t" << s3 << endl;
        cout << "s5\t" << s5 << endl;
        s3.clear();
        cout << "s3\t" << s3 << endl;
        s5.insert(40);
        cout << "Found 40 in:\t" << s3.find(40) << endl;
    }
    {
        Complex co1(1, -2);
        Complex co2(1.9, -2.3);
        Complex co3(2, -7);
        Complex co4(1.4, -4.1);
        Complex co5(-2, -1);
        vector<Complex> temp1 = { co1, co2 };
        vector<Complex> temp2 = { co1, co2, co3, co4, co5 };
        Set<Complex> s1(temp1), s2(temp2), s3, s4;
        s1.is_elem(co3);
        s1.insert(co4);
        cout << "s1:\t" << s1 << endl;
        s2.erase(co2);
        cout << "s2:\t" << s2 << endl;
        s3 = s1.common(s2);
        s4 = s1.sum(s2);
        cout << "s3\t" << s3 << endl;
        cout << "s4\t" << s4 << endl;
        Set<Complex> s5(s1);
        cout << "s5\t" << s5 << endl;
        s5 = s4;
        cout << "s5\t" << s5 << endl;
        cout << "s5 size:\t" << s5.size() << endl;
        s3.swap(s5);
        cout << "s3\t" << s3 << endl;
        cout << "s5\t" << s5 << endl;
        s3.clear();
        cout << "s3\t" << s3 << endl;
        s5.insert(co3);
        cout << "found 'co3' in:\t" << s5.find(co3) << endl;
    }
    return 0;
}
