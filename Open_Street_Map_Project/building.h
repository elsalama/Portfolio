/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "nodes.h"


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  std::string Name;
  std::string StreetAddress;
  std::vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, std::string name, std::string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  void print(const Nodes& nodes);

};
