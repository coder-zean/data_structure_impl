#include "kmp.h"

#include <string>
#include <iostream>
using namespace std;

int main() {
    string s = "abacababc";
    string p = "abab";
    cout << KmpUtil::DoKmp(s, p) << endl;  // expect: 4
    return 0;
}