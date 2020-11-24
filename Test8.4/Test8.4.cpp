#include "List.h"

int main()
{
    int n = 5; // 人数
    int m = 2; // 报数
    SList<int> loop;
    while (1) {
        cout << "请输入人数n和报数m:" << endl;
        cin >> n >> m;
        for (int i = n; i > 0; --i) loop.add(i);
        while (loop.getSize() != 1) {
            loop.forward(m - 1);
            loop.erase();
            //cout << loop.erase() << "\t";

        }
        cout << loop.getVal() << endl;
        loop.clear();
    }
}

