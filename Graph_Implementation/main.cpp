/*main.cpp*/
// summary:
// these are 5 non trivial test cases for the graph class
// we test to see if all functional and timing requirements
// are met
// 
// name: Elsa Viviana Lama
//
// Northwestern University
// CS 211: Winter 2023
//

#include "graph.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>

// general
// here we create a graph and make a combination of several tests
// we call a combination of several methods some we expect to ass
// some we expect to fail
// we also test whether the correct output for neighbour and vertices
// are being returned
TEST(testing, general) {
  graph Graph{};
  double weight1;
  ASSERT_TRUE(!Graph.getWeight("F", "G", weight1));
  ASSERT_TRUE(Graph.NumEdges() == 0);
  ASSERT_TRUE(Graph.NumVertices() == 0);
  ASSERT_TRUE(Graph.NumVertices() == 0);
  ASSERT_TRUE(Graph.neighbors("B") == std::set<std::string>{});
  ASSERT_TRUE(Graph.addVertex("A"));
  ASSERT_TRUE(Graph.addVertex("B"));
  ASSERT_TRUE(Graph.addVertex("C"));
  ASSERT_TRUE(Graph.addVertex("D"));
  ASSERT_TRUE(Graph.addVertex("E"));
  ASSERT_TRUE(Graph.addVertex("F"));
  ASSERT_TRUE(Graph.addVertex("G"));
  ASSERT_TRUE(Graph.addVertex("H"));
  ASSERT_TRUE(Graph.NumVertices() == 8);
  ASSERT_TRUE(!Graph.addVertex("A"));
  ASSERT_TRUE(!Graph.addVertex("H"));
  ASSERT_TRUE(!Graph.addVertex("C"));
  ASSERT_TRUE(Graph.addEdge("A", "B", 3.142));
  ASSERT_TRUE(Graph.addEdge("D", "E", 12.142));
  ASSERT_TRUE(Graph.addEdge("E", "F", 7.42));
  ASSERT_TRUE(Graph.addEdge("F", "G", 0.142));
  ASSERT_TRUE(Graph.addEdge("G", "H", 0.142));
  ASSERT_TRUE(Graph.addEdge("H", "A", 0.142));
  ASSERT_TRUE(Graph.addEdge("B", "C", 3.142));
  ASSERT_TRUE(Graph.addEdge("B", "C", 6.142));
  ASSERT_TRUE(Graph.addEdge("H", "E", -23.142));
  ASSERT_TRUE(Graph.addEdge("G", "G", 0));
  ASSERT_TRUE(Graph.addEdge("G", "G", -1));
  ASSERT_TRUE(Graph.addEdge("A", "B", 0));
  ASSERT_TRUE(Graph.addEdge("B", "B", 9.64));
  ASSERT_TRUE(Graph.addEdge("B", "D", 9.64));
  ASSERT_TRUE(Graph.addEdge("H", "H", 4.99));
  ASSERT_TRUE(Graph.addEdge("H", "C", 8.452));
  ASSERT_TRUE(Graph.NumEdges() == 13);
  double weight;
  ASSERT_TRUE(Graph.getWeight("F", "G", weight));
  ASSERT_DOUBLE_EQ(weight, 0.142);
  ASSERT_TRUE(!Graph.getWeight("X", "G", weight));
  ASSERT_TRUE(!Graph.getWeight("F", "Z", weight));
  ASSERT_TRUE(!Graph.getWeight("X", "Y", weight));
  ASSERT_TRUE(!Graph.getWeight("D", "H", weight));
  std::set<std::string> ngb{"B", "C", "D"};
  ASSERT_TRUE(Graph.neighbors("B") == ngb);
  // Graph.print(std::cout);
}

// getweight
// here we put various weights from nevative numbers
// to decimal points to zero
// we also put some weights twice
// we test if it behaves correctly
TEST(testing, getweight) {
  graph Graph{};
  double weight;
  ASSERT_TRUE(!Graph.getWeight("X", "G", weight));
  ASSERT_TRUE(Graph.addVertex("1"));
  ASSERT_TRUE(Graph.addVertex("2"));
  ASSERT_TRUE(Graph.addVertex("3"));
  ASSERT_TRUE(Graph.addVertex("4"));
  ASSERT_TRUE(Graph.addVertex("5"));
  ASSERT_TRUE(Graph.addVertex("6"));
  ASSERT_TRUE(Graph.addVertex("7"));
  ASSERT_TRUE(Graph.addVertex("8"));
  ASSERT_TRUE(Graph.addVertex("9"));
  ASSERT_TRUE(Graph.addVertex("10"));
  ASSERT_TRUE(Graph.addEdge("1", "2", 3.01));
  ASSERT_TRUE(Graph.addEdge("2", "3", 4.01));
  ASSERT_TRUE(Graph.addEdge("10", "4", 5.01));
  ASSERT_TRUE(Graph.addEdge("9", "5", 6.01));
  ASSERT_TRUE(Graph.addEdge("8", "6", 7.01));
  ASSERT_TRUE(Graph.addEdge("7", "7", 8.01));
  ASSERT_TRUE(Graph.addEdge("6", "8", 9.01));
  ASSERT_TRUE(Graph.addEdge("5", "9", 10.01));
  ASSERT_TRUE(Graph.addEdge("4", "10", 11.01));
  ASSERT_TRUE(Graph.addEdge("3", "7", 12.01));
  ASSERT_TRUE(Graph.addEdge("2", "6", 13.01));
  ASSERT_TRUE(Graph.addEdge("1", "5", 14.01));
  ASSERT_TRUE(Graph.addEdge("1", "4", 15.01));
  ASSERT_TRUE(Graph.addEdge("1", "3", 16.01));
  ASSERT_TRUE(Graph.addEdge("1", "2", 17.01));
  ASSERT_TRUE(Graph.getWeight("1", "2", weight));
  ASSERT_DOUBLE_EQ(weight, 17.01);
  ASSERT_TRUE(!Graph.getWeight("10", "9", weight));
  ASSERT_TRUE(!Graph.getWeight("x", "2", weight));
  ASSERT_TRUE(!Graph.getWeight("1", "y", weight));
  ASSERT_TRUE(!Graph.getWeight("x", "y", weight));
  ASSERT_TRUE(Graph.getWeight("7", "7", weight));
  ASSERT_DOUBLE_EQ(weight, 8.01);
}
// neihbours
// we add neighbours and test if they are correctly returned
// we also test self neighbours with edges to self
// we aslo test if we get correct ouput when we try to 
// get neighbours of non existed edges
// and non esistent vertices
TEST(testing, neihbours) {
  graph Graph{};
  ASSERT_TRUE(Graph.neighbors("B") == std::set<std::string>{});
  ASSERT_TRUE(Graph.addVertex("Soledar"));
  ASSERT_TRUE(Graph.addVertex("Bakhmut"));
  ASSERT_TRUE(Graph.addVertex("Kyv"));
  ASSERT_TRUE(Graph.addVertex("Luhansk"));
  ASSERT_TRUE(Graph.addVertex("Kromatosk"));
  ASSERT_TRUE(Graph.addVertex("Slovyansk"));
  ASSERT_TRUE(Graph.addVertex("Crimea"));
  ASSERT_TRUE(Graph.addVertex("Moscow"));
  ASSERT_TRUE(Graph.addVertex("Belarus"));
  ASSERT_TRUE(Graph.addVertex("Kherson"));
  ASSERT_TRUE(Graph.neighbors("Crimea") == std::set<std::string>{});
  ASSERT_TRUE(Graph.neighbors("Kyv") == std::set<std::string>{});
  ASSERT_TRUE(Graph.addEdge("Soledar", "Bakhmut", 150));
  ASSERT_TRUE(Graph.addEdge("Bakhmut", "Soledar", 130));
  ASSERT_TRUE(Graph.addEdge("Bakhmut", "Kromatosk", 150));
  ASSERT_TRUE(Graph.addEdge("Kromatosk", "Bakhmut", 120));
  ASSERT_TRUE(Graph.addEdge("Bakhmut", "Slovyansk", 1520));
  ASSERT_TRUE(Graph.addEdge("Slovyansk", "Bakhmut", 140));
  ASSERT_TRUE(Graph.addEdge("Kyv", "Slovyansk", 100));
  ASSERT_TRUE(Graph.addEdge("Slovyansk", "Kyv", 190));
  ASSERT_TRUE(Graph.addEdge("Kyv", "Kherson", 190));
  ASSERT_TRUE(Graph.addEdge("Kherson", "Kyv", 180));
  ASSERT_TRUE(Graph.addEdge("Kyv", "Belarus", 170));
  ASSERT_TRUE(Graph.addEdge("Belarus", "Kyv", 160));
  ASSERT_TRUE(Graph.addEdge("Kyv", "Moscow", 150));
  ASSERT_TRUE(Graph.addEdge("Moscow", "Kyv", 140));
  ASSERT_TRUE(Graph.addEdge("Kyv", "Crimea", 130));
  ASSERT_TRUE(Graph.addEdge("Crimea", "Kyv", 120));
  std::set<std::string> ngh{"Slovyansk", "Kherson", "Belarus", "Moscow",
                            "Crimea"};
  ASSERT_TRUE(Graph.neighbors("Kyv") == ngh);
  std::set<std::string> ngh2{"Soledar", "Kromatosk", "Slovyansk"};
  ASSERT_TRUE(Graph.neighbors("Bakhmut") == ngh2);
}
// getvertices
// this is the simplests of tests
// we get vertices from an empty graph and
// see if output is correct
// we add vertices twice to see if a false is returned
// we check that all added vertices are returned
TEST(testing, getvertices) {
  graph Graph{};
  ASSERT_TRUE(Graph.getVertices() == std::vector<std::string>{});
  ASSERT_TRUE(Graph.addVertex("Goma"));
  ASSERT_TRUE(Graph.addVertex("Sake"));
  ASSERT_TRUE(Graph.addVertex("Kitchanga"));
  ASSERT_TRUE(Graph.addVertex("Kigali"));
  ASSERT_TRUE(Graph.addVertex("Bunagana"));
  ASSERT_TRUE(Graph.addVertex("Kinsasha"));
  ASSERT_TRUE(Graph.addVertex("Congo"));
  ASSERT_TRUE(Graph.addVertex("Rwanda"));
  ASSERT_TRUE(Graph.addVertex("Uganda"));
  ASSERT_TRUE(Graph.addEdge("Goma", "Sake", 763));
  ASSERT_TRUE(Graph.addEdge("Sake", "Kitchanga", 223340));
  ASSERT_TRUE(Graph.addEdge("Kitchanga", "Kigali", 0));
  ASSERT_TRUE(Graph.addEdge("Kigali", "Bunagana", 10));
  ASSERT_TRUE(Graph.addEdge("Bunagana", "Kinsasha", 50));
  ASSERT_TRUE(Graph.addEdge("Kinsasha", "Congo", 12750));
  ASSERT_TRUE(Graph.addEdge("Congo", "Rwanda", 123150));
  ASSERT_TRUE(Graph.addEdge("Rwanda", "Uganda", 15230));
  ASSERT_TRUE(Graph.addEdge("Uganda", "Goma", 1234));
  ASSERT_TRUE(Graph.addEdge("Goma", "Congo", 312));
  ASSERT_TRUE(Graph.addEdge("Congo", "Sake", 345));
  ASSERT_TRUE(Graph.addEdge("Kigali", "Rwanda", 223));
  ASSERT_TRUE(Graph.addEdge("Kitchanga", "Uganda", 342));
  ASSERT_TRUE(Graph.addEdge("Goma", "Bunagana", 345));
  ASSERT_TRUE(Graph.addEdge("Bunagana", "Sake", 123));

  std::vector<std::string> verts{"Goma",   "Sake",     "Kitchanga",
                                 "Kigali", "Bunagana", "Kinsasha",
                                 "Congo",  "Rwanda",   "Uganda"};
  ASSERT_TRUE(Graph.getVertices() == verts);
}
// stress test
// we create a vector of a million random strings
// we also create another vector of a million edges and wheigts
// we add all the edges and vertices to the grpah
// takes 5 minutes
TEST(testing, stresstest) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::string str(
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  const int size = 1'000'000;
  std::vector<std::string> verts;
  for (int i = 0; i < size; ++i) {
    std::shuffle(str.begin(), str.end(), mt);
    verts.push_back(str.substr(0, 32));
  }
  std::vector<std::tuple<int, int, double>> edges;
  std::uniform_real_distribution<double> dist(1.0, 10.0);
  std::uniform_int_distribution<int> int2(0, size - 1);
  for (int i = 0; i < size; ++i) {
    edges.push_back(std::make_tuple(int2(mt), int2(mt), dist(mt)));
  }
  graph Graph{};
  for (int i = 0; i < size; ++i) {
    ASSERT_TRUE(Graph.addVertex(verts[i]));
  }
  for (int i = 0; i < size; ++i) {
    ASSERT_TRUE(Graph.addEdge(verts[std::get<0>(edges[i])],
                              verts[std::get<1>(edges[i])], std::get<2>(edges[i])));
  }
}

int main() {
  ::testing::InitGoogleTest();

  //
  // run all the tests, returns 0 if they
  // all pass and 1 if any fail:
  //
  int result = RUN_ALL_TESTS();

  return result;
}

/*
 * rsync -aP .
 * evl3331@moore.wot.eecs.northwestern.edu:/home/evl3331/project08/release
 *
 * Pedro6812.
 * rsync -aP
 * evl3331@moore.wot.eecs.northwestern.edu:/home/evl3331/project08/release/ .
 */
