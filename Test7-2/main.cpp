#include <iostream>
#include "Set.h"

int main() {
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
    return 0;
}
