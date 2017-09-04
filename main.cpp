#include <string>
#include <iostream>
#include "evaluate.h"

using namespace std;

int main()
{
    string s;
    double ret;

    cout << "please input your evaluate: " ;
    cin >> s;

    cout << s << endl;

    ret = Calculate(s);

    cout << "Your answer is:" << ret << endl;

    return 0;
}
