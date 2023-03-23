#include <iostream>

using namespace std;

class Test {
public:
  Test() {}
  int a = 0;
  int b = 100;
};

int main() {
  Test t;
  Test* tt = &t;
  delete tt;
  return 0;
}