// Jacob Zamore
// Driver file demonstrating efficacy of computeMST on a sample weighted graph
#include <iostream>

#include <fstream>

#include <sstream>

#include <string>

#include <algorithm>

#include "WGraph.h"

using namespace std;

int main(int argc, char * argv[]) {
  string fileName = argv[1];
  ifstream file(fileName);
  int N;
  file >> N;
  file.close();
  WGraph myGraph(N); // Create a weighted graph of size N on the stack.
  string line;
  double weight;
  for (unsigned int colNum = 0; colNum < N; ++colNum) {
    ifstream file(fileName);
    getline(file, line); // Eat the first line
    for (unsigned int j = 0; j < N; ++j) {
      // Loop through j lines of the file
      getline(file, line);
      istringstream lineStream(line);
      // Grab the double from the lineStream at the colNumth position
      // grab double at position 3
      int doubleIndex = 0;
      double doubleToGrab; // represents our weight
      while (doubleIndex < colNum + 1) {
        lineStream >> doubleToGrab;
        doubleIndex++;
      }
      // If weight isn't 0, we have an adjacent edge, so add it to WGraph
      if (doubleToGrab != 0) {
        myGraph.addEdge(colNum, j, doubleToGrab);
      }
    }
    file.close();
  }
  // myGraph succesfully created, now call computeMST
  myGraph.computeMST();
}

