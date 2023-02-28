#include <iostream>

using namespace std;

class Test1{
public:
  void abdfe() {
    cout << "ab" << endl;
  }
};

class Test2 {
public:
  int abc;
};

class Test : public Test1 {

  void t() {

  }

  static void ab() {

  }

  void abc() {

  }
private:
  // int a = 100;
};

int main() {
  Test a;
  cout << sizeof(a) << endl;
  return 0;
}