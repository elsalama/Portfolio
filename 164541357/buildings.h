/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <vector>
#include "footways.h"
#include "building.h"
#include "tinyxml2.h"

//
// Keeps track of all the buildings in the map.
//
class Buildings {
public:
  std::vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(tinyxml2::XMLDocument &xmldoc);

  //
  // accessors / getters
  //
  int getNumMapBuildings();

  void print();

  void findAndPrint(const std::string&, const Nodes&, const Footways&);
};
