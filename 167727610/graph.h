/*graph.h*/

//
// Graph class implemented as an Adjacency List. each entry in the Adjacency List is shadowed
// with an entry into a vector of vetex names such that same index refers to the same vertex on
// both adjacency list and vertex name containers
// 
// the Adjacency List is implemented as a vector of maps where the vectors index represents the
// vertex and the map at that location represents the neighbours' index and their respective wheights
// 
// for easily searching of the vertex names in logarithimic time we also mantain another map that associates each of the
// vertex name to its index so that the Adjacency List and vertec names containers can easily be refefenced
// 
//   
//
// For this implementation of graph, the vertices are
// string, and the weights are doubles.  Example:
//
//   graph  G;
//   G.addVertex("Chicago");
//   G.addVertex("New York");
//   G.addEdge("Chicago", "New York", -999.99);
//
// name: Elsa Viviana Lama
//
// Northwestern University
// CS 211: Winter 2023
//
#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <map>

class graph {
private:
  std::vector<std::string>    Vertices;
  std::map<std::string, int>  Vertex2Index;
  std::vector<std::map<int, double>> Edges;
  int EdgeCount;

  int _LookupVertex(long long v) const;

public:
  //
  // default constructor: no parameters
  //
  graph();

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const;

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const;

  //
  // addVertex
  //
  // Adds the vertex v to the graph and returns true. However,
  // if v is already in the graph, it is not added again and
  // false is returned.
  //
  bool addVertex(std::string v);

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true. If the vertices do not exist then no edge is added
  // and false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(std::string from, std::string to, double weight);

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned. If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(std::string from, std::string to, double &weight) const;

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge. If
  // v does not exist, an empty set is returned.
  //
  std::set<std::string> neighbors(std::string v) const;

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph. There is no guaranteed order to the vertices
  // in the returned vector; the order should be considered
  // random.
  //
  std::vector<std::string> getVertices() const;

  //
  // print
  //
  // Prints the internal state of the graph to the given
  // output stream for debugging purposes. The output will
  // contain the # of vertices, the # of edges, the vertices,
  // and the edges. Vertices are output as strings and the
  // weights as doubles.
  //
  // Example:
  //    graph G;
  //    ...
  //    G.print(cout);  // print to console
  //
  void print(std::ostream &output) const;
};
