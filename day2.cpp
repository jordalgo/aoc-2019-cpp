#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct ProgramState {
  int lastCode;
  int position;
  vector<int> program;
};

vector<int> getProgram() {
  vector<int> vec;
  std::ifstream in("day2-input.txt");
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

ProgramState runProgram(ProgramState state) {
  auto code = state.program[state.position];
  auto nextState = state;
  nextState.lastCode = code;
  nextState.position = state.position + 4;
  switch(code) {
      case 1 :
      case 2 : {
        int pos1 = state.program[state.position + 1];
        int valAtPos1 = state.program[pos1];
        int pos2 = state.program[state.position + 2];
        int valAtPos2 = state.program[pos2];
        int pos3 = state.program[state.position + 3];
        int result = (code == 1) ? valAtPos1 + valAtPos2 : valAtPos1 * valAtPos2;
        nextState.program[pos3] = result;
        return nextState;
      }
      case 99 : {
        return nextState;
      }
      default :
         throw runtime_error("Bad Code");
   }
}

int runProgramWithInputs(int noun, int verb, vector<int> program) {
  program[1] = noun;
  program[2] = verb;
  struct ProgramState nextState = {0, 0, program};
  while (nextState.lastCode != 99) {
    nextState = runProgram(nextState);
  }
  return nextState.program[0];
}

int main() {
  auto program = getProgram();
  vector<int> testProgram{ 1,9,10,3,2,3,11,0,99,30,40,50 };

  cout << runProgramWithInputs(12, 2, program) << endl;

  vector<int> range1(100);
  iota(range1.begin(), range1.end(), 0);
  auto range2 = range1;
  int end = 19690720;

  for (auto noun : range1) {
    for (auto verb : range2) {
      auto result = runProgramWithInputs(noun, verb, program);
      if (result == end) {
        cout << noun << endl;
        cout << verb << endl;
        break;
      }
    }
  }

  return 0;
}
