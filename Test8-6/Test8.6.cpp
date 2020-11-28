#include "hashTable.h"
//unsigned int hashFunction(const string& str) {
//    auto it = str.begin();
//    unsigned int hash = 1315423911;
//    while (it != str.end()) {
//        hash ^= ((hash << 5) + *(it++) + (hash >> 2));
//    }
//    return (hash & 0x0000FFFF);
//}
int main()
{
    hashTable ht;
    Node p1("xiaozikai", "13412345678", "666666", "wuhan");
    Node p2("luojingwei", "13893445438", "223413", "wuhan");
    Node p3("liujianghang", "18983750331", "738068", "wuhan");
    Node p4("liujianghang", "12345750331", "738068", "wuhan");
    ht.makePair("xiaozikai", p1);
    ht.makePair("luojingwei", p2);
    ht.makePair("liujianghang", p3);
    ht.makePair("liujianghang", p4);
    ht.find("liujianghang");
    ht.erase("liujianghang");
    ht.find("liujianghang");
    int i=0;
    //while (1) {
    //    string strIn;
    //    cout << "请输入:\t";
    //    cin >> strIn;
    //    cout << hashFunction(strIn) << endl;
    //}
}
