#include <iostream>
#include "numberGroups.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    NumberGroups numbers;
    numbers.printGroups(argv[1]);
  }
  return 0;
}
