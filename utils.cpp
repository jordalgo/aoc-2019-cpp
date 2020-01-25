#include "utils.h"

#include <fstream>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> getProgram(std::string fileName) {
  vector<int> vec;
  std::ifstream in(fileName);
  std::string line;

  if(!in) {
    cerr << "Cannot open the File : " << endl;
  }

  while(getline(in, line, ',')) {
    if (line.size() > 0) {
      vec.push_back(stoi(line));
    }
  }
  in.close();
  return vec;
}
