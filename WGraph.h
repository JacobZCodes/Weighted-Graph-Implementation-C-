// Jacob Zamore
// Header file for a weighted, undirected graph augmented with a computeMST method which uses Kruskal's algorithm to find the MST for a given graph
#ifndef WGraph_H
#define WGraph_H
#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include "DblList.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

//a weighted, undirected WGraph implemented with adjacency matrix
//fixed size
using namespace std;
typedef unsigned int VertexID;

class WGraph{
public: 
  struct Edge { // Edge represented as a struct, which is kind of like a baby-psuedo class - ChatGPT 
      unsigned int vertex1;
      unsigned int vertex2;

      Edge(unsigned int v1, unsigned int v2) : vertex1(v1), vertex2(v2) {} // ChatGPT
      
      Edge() : vertex1(10000), vertex2(10000) {}   // Default constructor to appease compiler

      bool operator<(const Edge& other) const { // m_edgeSet and m_resultSet are sets whose elements are edges; operator info needed here because I don't want redundant edges
                                                // in my code ie the edge with vertex1=1 and vertex2=3 is the same as the "other" edge whose vertex1=3 and vertex2=1
          auto orderedThis = std::minmax(vertex1, vertex2); // ChatGPT, auto keyword automatically identifies the type 
          auto orderedOther = std::minmax(other.vertex1, other.vertex2);
          return orderedThis < orderedOther;
      }
  };

  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
  double getWeight(VertexID i, VertexID j);
  void buildEdgeSet();
  set<Edge>& getEdgeSet();
  void printEdgeSet(const set<Edge>& edgeSet);
  Edge getMinEdge();
  void viewVertexSets();
  set<Edge>& getResultSet();
  DblList<set<VertexID>>& getVertexSets();
  set<VertexID> findMatchingSet(VertexID vertex);
  std::set<unsigned int> unionizeSets(const std::set<unsigned int> set1, const std::set<unsigned int> set2);
  void displayMSTMatrix();
  double calculateMSTCost();
  void computeMST();

private:
  double** m_MSTAdj;
  double** m_adj; //is there an edge between two vertices and what's the weight of the edge
  double** m_conn; //more general, is there a path between a start and a finish and what's the cost (all parts summed)
  unsigned int m_size; //nodes in WGraph (fixed)
  set<Edge> m_edgeSet;
  set<Edge> m_resultSet;
  DblList<set<VertexID>> m_vertexSets;
};

#endif