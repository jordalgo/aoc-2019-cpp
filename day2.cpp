#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

struct ProgramState {
  int lastCode;
  int position;
  vector<int> program;
};

ProgramState runProgram(ProgramState state) {
  auto code = state.program[state.position];
  state.lastCode = code;
  switch(code) {
      case 1 :
      case 2 : {
        int pos1 = state.program[state.position + 1];
        int valAtPos1 = state.program[pos1];
        int pos2 = state.program[state.position + 2];
        int valAtPos2 = state.program[pos2];
        int pos3 = state.program[state.position + 3];
        int result = (code == 1) ? valAtPos1 + valAtPos2 : valAtPos1 * valAtPos2;
        state.program[pos3] = result;
        state.position = state.position + 4;
        return state;
      }
      case 99 : {
        return state;
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
  auto program = getProgram("day2-input.txt");
  vector<int> testProgram{ 1,9,10,3,2,3,11,0,99,30,40,50 };

  cout << runProgramWithInputs(12, 2, program) << endl;

  vector<int> range1(100);
  iota(range1.begin(), range1.end(), 0);
  auto range2 = range1;
  int end = 19690720;

  for (auto noun : range1) {
    int result;
    for (auto verb : range2) {
      result = runProgramWithInputs(noun, verb, program);
      if (result == end) {
        cout << noun << endl;
        cout << verb << endl;
        break;
      }
    }
    if (result == end) {
      break;
    }
  }

  return 0;
}
