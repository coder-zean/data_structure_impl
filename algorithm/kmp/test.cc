#include "kmp.h"

#include <string>
#include <iostream>
using namespace std;

int main() {
    string s = "mississippi";
    string p = "issip";
    cout << KmpUtil::DoKmp(s, p) << endl;  // expect: 4
    return 0;
}
