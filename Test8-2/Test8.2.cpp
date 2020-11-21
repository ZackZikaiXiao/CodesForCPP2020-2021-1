#include "Stack.h"
#include "Calculator.h"
#include "DFA.h"
int main() {
	string exp;
	Calculator cclt;
	while (1) {
		cout << ">>";
		getline(cin, exp);
		try { cout << cclt.doIt(exp) << endl; }
		catch (exception e) { cout << e.what() << endl; }
	}
	system("pause");
	

	/*词法分析测试*/
	//string exp;
	//DFA dfa;
	//dfa.addID("num1", 666);
	//while (1) {
	//	cout << ">>";
	//	getline(cin, exp);
	//	dfa.catchExpIn(exp);
	//	dfa.debugShow();
	//}
	//system("pause");

}