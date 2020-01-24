#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getFuel(int mass) {
  return (floor(mass / 3) - 2);
}

int getTotalFuel(int mass) {
  int total = 0;
  int next = getFuel(mass);
  while (next > 0) {
    total += next;
    next = getFuel(next);
  }
  return total;
}

vector<int> getFileInts() {
  vector<int> vec;
  std::ifstream in("day1-input.txt");
  std::string line;

  if(!in) {
    cerr << "Cannot open the File : " << endl;
  }

  while(getline(in, line)) {
    if (line.size() > 0) {
      vec.push_back(stoi(line));
    }
  }
  in.close();
  return vec;
}

int main() {
  auto ints = getFileInts();
  auto total = accumulate(ints.begin(), ints.end(), 0, [](int a, int b){ return a + getFuel(b); });
  cout << total << endl;

  auto total2 = accumulate(ints.begin(), ints.end(), 0, [](int a, int b){ return a + getTotalFuel(b); });
  cout << total2 << endl;

  return 0;
}
