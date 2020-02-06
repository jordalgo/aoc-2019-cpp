#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<std::string> getWires() {
  vector<std::string> vec;
  std::ifstream in("day3-input.txt");
  std::string line;

  if(!in) {
    cerr << "Cannot open the File : " << endl;
  }

  while(getline(in, line)) {
    if (line.size() > 0) {
      vec.push_back(line);
    }
  }
  in.close();
  return vec;
}

vector<std::string> getWireInstructions(std::string wire) {
  vector<std::string> instructions;
  std::string line;
  std::stringstream ss(wire);

  while(getline(ss, line, ',')) {
    if (line.size() > 0) {
      instructions.push_back(line);
    }
  }

  return instructions;
}

struct Coordinate {
  int x;
  int y;
};

struct Line {
  Coordinate start;
  Coordinate end;
};

struct IntersectingLines {
  Line line1;
  Line line2;
};

using Path = std::vector<Line>;

Coordinate getNextCoordinate(Coordinate start, std::string instruction) {
  auto x = start.x;
  auto y = start.y;
  auto direction = instruction.front();
  auto amount = stoi(instruction.substr(1, string::npos));
  switch (direction) {
    case 'R':
      return {(x + amount), y};
    case 'L':
      return {(x - amount), y};
    case 'U':
      return {x, (y + amount)};
    case 'D':
      return {x, (y - amount)};
    default:
      throw runtime_error("Bad Direction");
  }
}

bool isLineVertical(Line line) {
  return line.start.x == line.end.x;
}

bool doLinesIntersect(Line line1, Line line2) {
  const auto line1IsVertical(isLineVertical(line1));
  const auto line2IsVertical(isLineVertical(line2));
  if (line1IsVertical && line2IsVertical) {
    return false;
  }
  const auto verticalLine = line1IsVertical ? line1 : line2;
  const auto horizontalLine = line1IsVertical ? line2 : line1;

  return (
      (
       (verticalLine.start.y >= horizontalLine.start.y
        && verticalLine.end.y <= horizontalLine.end.y)
       ||
       (verticalLine.start.y <= horizontalLine.start.y
        && verticalLine.end.y >= horizontalLine.end.y))
      &&
      (
        (verticalLine.start.x >= horizontalLine.start.x
         && verticalLine.start.x <= horizontalLine.end.x)
        ||
        (verticalLine.start.x <= horizontalLine.start.x 
         && verticalLine.start.x >= horizontalLine.end.x)));
}

vector<IntersectingLines> getIntersectingLines(Path path1, Path path2) {
  vector<IntersectingLines> intersectingLines;
  for (auto line1 : path1) {
    for (auto line2: path2) {
      if (doLinesIntersect(line1, line2)) {
        intersectingLines.push_back({line1, line2});
      }
    }
  }
  return intersectingLines;
}

vector<Coordinate> buildLineCoordinates(Line line) {
  vector<Coordinate> coords;
  auto startX = line.start.x < line.end.x ? line.start.x : line.end.x;
  auto endX = line.start.x < line.end.x ? line.end.x : line.start.x;
  auto startY = line.start.y < line.end.y ? line.start.y : line.end.y;
  auto endY = line.start.y < line.end.y ? line.end.y : line.start.y;

  for (int x = startX; x <= endX; x++) {
    for (int y = startY; y <= endY; y++) {
      coords.push_back({x, y});
    }
   }
  return coords;
}

Coordinate getIntersectionPoint(IntersectingLines lines) {
  auto coords1 = buildLineCoordinates(lines.line1);
  auto coords2 = buildLineCoordinates(lines.line2);
  for (const auto c1 : coords1) {
    for (const auto c2: coords2) {
      if (c1.x == c2.x && c1.y == c2.y) {
        return {c1.x, c2.y};
      }
    }
  }
  throw "No interesection point found";
}

int getManhattanDistance(Coordinate coord) {
  return abs(coord.x) + abs(coord.y);
}

vector<Line> getLines(vector<std::string> instructions) {
  Coordinate prevCoordinate = {0,0};
  vector<Line> lines;
  for (auto instruction : instructions) {
    auto nextCoordinate = getNextCoordinate(prevCoordinate, instruction);
    lines.push_back({prevCoordinate, nextCoordinate});
    prevCoordinate = nextCoordinate;
  }
  return lines;
}

int main() {
  auto wires = getWires();
  vector<vector<std::string>> instructions;
  instructions.resize(wires.size());
  std::transform (wires.begin(), wires.end(), instructions.begin(), getWireInstructions);

  vector<Path> wirePaths;
  wirePaths.resize(wires.size());
  std::transform (instructions.begin(), instructions.end(), wirePaths.begin(), getLines);

  auto intersectingLines = getIntersectingLines(wirePaths[0], wirePaths[1]);
  vector<Coordinate> intersectionPoints;
  intersectionPoints.resize(intersectingLines.size());

  std::transform (intersectingLines.begin(), intersectingLines.end(), intersectionPoints.begin(), getIntersectionPoint);

  vector<int> distances;
  distances.resize(intersectionPoints.size());
  std::transform (intersectionPoints.begin(), intersectionPoints.end(), distances.begin(), getManhattanDistance);

  int minDistance = 0;

  for (auto d: distances) {
    if (d != 0) {
      if (minDistance == 0) {
        minDistance = d;
      } else if (minDistance > d) {
        minDistance = d;
      }
    }
  }

  cout << minDistance << endl;

  return 0;
}
