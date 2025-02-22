/*footway.h*/

//
// A footway / path in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <vector>



//
// Footway
//
// Stores info about one footway in the map.  The ID uniquely identifies
// the footway.  The vector defines points (Nodes) along the footway; the
// vector always contains at least two points.
//
// Example: think of a footway as a sidewalk, with points n1, n2, ..., 
// nx, ny.  n1 and ny denote the endpoints of the sidewalk, and the points
// n2, ..., nx are intermediate points along the sidewalk.
//
class Footway
{
public:
  long long ID;
  std::vector<long long> NodeIDs;

  //
  // constructor
  //
  Footway(long long id);

  //
  // adds the given nodeid to the end of the vector
  //
  void add(long long nodeid);

  bool operator==(const Footway&);

  bool operator<(const Footway&);

};
