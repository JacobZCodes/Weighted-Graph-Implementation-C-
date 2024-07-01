// Jacob Zamore
// Implementation file for a weighted, undirected graph augmented with a computeMST method which uses Kruskal's algorithm to find the MST for a given graph

#include "WGraph.h"
#include <iomanip>

WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
  m_conn = NULL;
}

WGraph::WGraph(unsigned int sz){
  m_size = sz;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz];
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(unsigned int i = 0; i < m_size; ++i){
    for(unsigned int j = 0; j < m_size; ++j){
      m_adj[i][j] = std::numeric_limits<double>::max(); //essentially infinity
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
    set<VertexID> singleVertexSet = {i};
    m_vertexSets.addFront(singleVertexSet); // Assuming DblList has an 'add' method
  }
}

WGraph::~WGraph(){
  //release memory
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}


void WGraph::calcFW(){ //runtime complexity O(v^3)
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }
  for(int im = 0; im < m_size; ++ im){ //intermediate points --> transitive closure
    for(int source = 0; source < m_size; ++source){ //source = starting point
      for(int sink = 0; sink <m_size; ++sink){ //sink = ending point
        if(source == sink){
          continue;
        }else if(m_conn[source][im] != std::numeric_limits<double>::max() &&
          m_conn[im][sink] != std::numeric_limits<double>::max() &&
          m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
           m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }
      }
    }
  }
}

double WGraph::cheapestCost(VertexID i, VertexID j){
  return m_conn[i][j]; //constant
}

double WGraph::getWeight(VertexID i, VertexID j) {
  return m_adj[i][j];
}

void WGraph::buildEdgeSet() {
  for (int i=0; i<m_size; i++) {
    for (int j=0; j<m_size; j++) {
      if (areAdjacent(i,j)) {
        // If vertices are adjacent, they're an edge
        Edge tempEdge(i,j);
        m_edgeSet.insert(tempEdge);
      }
    }
  }
}

void WGraph::printEdgeSet(const set<WGraph::Edge>& edgeSet) {
    for (const auto& edge : edgeSet) {
        std::cout << "Edge from vertex " << edge.vertex1 << " to vertex " << edge.vertex2 << "("  << m_adj[edge.vertex1][edge.vertex2] << ")" << endl;
    }
}

set<WGraph::Edge>& WGraph::getEdgeSet() {
  return m_edgeSet;
}

set<WGraph::Edge>& WGraph::getResultSet() {
  return m_resultSet;
}

DblList<set<VertexID>>& WGraph::getVertexSets() {
  return m_vertexSets;
}

WGraph::Edge WGraph::getMinEdge() {
    Edge minEdge(10000,10000); // I couldn't figure out how to work this with a priority queue, so this method finds the minimum weighted edge in the set
    double minWeight = 10000000;
    for (const Edge& edge : m_edgeSet) {
        if (m_adj[edge.vertex1][edge.vertex2] < minWeight) {
          minEdge = edge;
          minWeight = m_adj[edge.vertex1][edge.vertex2];
        }
    }
    m_edgeSet.erase(minEdge); // Once minimum edge is found, remove it from the set
    return minEdge;
}

void WGraph::viewVertexSets() { 
  cout << "Viewing Vertex Sets..." << endl;
  while (!m_vertexSets.isEmpty()) {
    set<VertexID> tempSet;
    tempSet = m_vertexSets.removeFront();
    for (VertexID vertex : tempSet) {
      cout << vertex << " ";
    }
    cout << endl;
  }
}

set<VertexID> WGraph::findMatchingSet(VertexID vertex) { // Parameter is one of the vertices of the most recent minEdge taken from our m_edgeSet. This method
                                                         // loops thorugh all the vertex sets and then combs these sets to see if that set contains our vertex parameter. Returns the matching set.
    for (unsigned int i = 0; i < m_vertexSets.getSize(); ++i) {
        const set<VertexID>& currentSet = m_vertexSets.get(i);

        // Check if the set contains the vertex
        if (currentSet.find(vertex) != currentSet.end()) { // ChatGPT

            return currentSet; 
        }
    }
    // Worst case
    return set<VertexID>();
}

// ChatGPT 
std::set<unsigned int> WGraph::unionizeSets(const std::set<unsigned int> set1, const std::set<unsigned int> set2) {
    std::set<unsigned int> resultSet;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(resultSet, resultSet.begin()));
    return resultSet;
}

void WGraph::displayMSTMatrix() {
m_MSTAdj = new double*[m_size];
// Initially set all values equal to 0.0
for (int a =0; a<m_size; ++a) {
  m_MSTAdj[a] = new double[m_size];
  for (int b=0; b<m_size; ++b) {
    m_MSTAdj[a][b] = 0.0;
  }
}
// Now we update adjacent edge values to their respective weights
  for (unsigned int i=0; i<m_size; i++) {
    for (unsigned int j=0; j<m_size; j++) {
      for (const Edge& e : m_resultSet) {
        // Loop through result set and see if our i,j is the same as one of the edges in resultSet
        if ((i == e.vertex1 && j == e.vertex2) || (i == e.vertex2 && j == e.vertex1)) {
          m_MSTAdj[i][j] = m_adj[i][j];
        }
      }
    }
  }
  // ChatGPT - this weird cout stuff is just so standard output prints floats instead of ints
  cout << fixed << setprecision(1);
  for (int c =0; c<m_size; ++c) {
    for (int d=0; d<m_size; ++d) {
      cout << setw(2) << m_MSTAdj[c][d] << " ";
    }
    cout << endl;
  }
}

void WGraph::computeMST() {
    this->buildEdgeSet(); // Populates m_edgeSet
    // this->overloaded constructor constructs a dbllist whose nodes are sets which are all initially of length 1 and whose elements are singular vertex ids
    // our edgeSet has been populated as well, which contains all edges whose weight != 0. our resultSet starts out as an empty set whose elements are edges. we can now
    // begin the algorithm
    set < VertexID > vSet1;
    set < VertexID > vSet2;
    while (this->getVertexSets().getSize() > 1 && this->getEdgeSet().size() > 0) {
      // This whole while loop is ripped pseudo-code from the Zybooks 10.18.3 MST Algorithm Participation Activity
      WGraph::Edge nextEdge = this->getMinEdge(); // grabs the lowest weighted edge from m_edgeSet and then erases the element from the set
      vSet1 = this->findMatchingSet(nextEdge.vertex1);
      vSet2 = this->findMatchingSet(nextEdge.vertex2);
      set<VertexID> tempSet;
      if (vSet1 != vSet2) {
        this->getResultSet().insert(nextEdge);
        // Iterate through m_vertexSets and remove vSet1 and vSet2
        for (unsigned int i = 0; i < this->getVertexSets().getSize(); ++i) {
        // Identifies which sets to remove from vertexSets
          if (this->getVertexSets().get(i) == vSet1 || this->getVertexSets().get(i) == vSet2) {
            this->getVertexSets().remove(i);
          }
        } 
        // Merge the two sets together and add the merged set back into this->getVertexSets()/m_vertexSetes
        set < VertexID > merged = this->unionizeSets(vSet1, vSet2);
        this->getVertexSets().addFront(merged);
      }
    }
    cout << fixed << setprecision(1);
    cout << "MST Cost is: " << this->calculateMSTCost() << "." << endl; 
    this->displayMSTMatrix();
}

double WGraph::calculateMSTCost() {
    double total=0;
    double currWeight;
    int i=0;
    for (const auto& edge : m_resultSet) {
        currWeight = m_adj[edge.vertex1][edge.vertex2];
        total+= currWeight;
    }
    return total;
}



