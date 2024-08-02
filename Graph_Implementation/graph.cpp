/*graph.cpp*/

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

#include "graph.h"
#include <algorithm>

graph::graph() : EdgeCount{0} {}

int graph::NumVertices() const { return Vertices.size(); }

int graph::NumEdges() const { return EdgeCount; }

bool graph::addVertex(std::string v) {
  if (Vertex2Index.count(v) == 0) {
    Vertices.push_back(v);
    Vertex2Index[v] = Vertices.size() - 1;
    Edges.push_back({});
    return true;
  }
  return false;
}

bool graph::addEdge(std::string from, std::string to, double weight) {
  if (!Vertex2Index.count(from) || !Vertex2Index.count(to)) {
    return false;
  }
  int frm = Vertex2Index[from];
  int tu = Vertex2Index[to];
  if (Edges[frm].count(tu) == 0) {
    EdgeCount++;
  }
  Edges[frm][tu] = weight;
  return true;
}

bool graph::getWeight(std::string from, std::string to, double &weight) const {
  if (!Vertex2Index.count(from) || !Vertex2Index.count(to)) {
    return false;
  }
  int frm = Vertex2Index.at(from);
  int tu = Vertex2Index.at(to);
  if (Edges.at(frm).count(tu) != 0) {
    weight = Edges.at(frm).at(tu);
    return true;
  }
  return false;
}

std::set<std::string> graph::neighbors(std::string v) const {
  if (!Vertex2Index.count(v)) {
     return std::set<std::string>{};
  }
  int vv = Vertex2Index.at(v);
  auto map = Edges.at(vv);
  std::set<std::string> neighbors;
  std::transform(map.begin(), map.end(),
                 std::inserter(neighbors, neighbors.begin()),
                 [this](const std::map<int, int>::value_type &pair) {
                   return Vertices[pair.first];
                 });
  return neighbors;
}

std::vector<std::string> graph::getVertices() const { return Vertices; }

void graph::print(std::ostream &output) const {
  output << "# of vertices: " << Vertices.size() << std::endl;
  output << "# of edges: " << EdgeCount << std::endl;
  output << "vertices: " << std::endl;
  for (const auto vertex : Vertices) {
    output << vertex << " ";
  }
  output << std::endl;
  for (const auto vertex : Vertices) {
    size_t index = Vertex2Index.at(vertex);
    if (index < Edges.size()) {
      auto map = Edges.at(index);
      for (const auto &item : map) {
        output << "from: " << vertex << " to: " << Vertices[item.first]
               << " weight: " << item.second << std::endl;
      }
    }
  }
}
