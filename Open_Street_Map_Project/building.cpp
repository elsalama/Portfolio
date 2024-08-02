/*building.cpp*/

//
// A building in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include "building.h"

//
// constructor
//
Building::Building(long long id, std::string name, std::string streetAddr)
    : ID(id), Name(name), StreetAddress(streetAddr) {
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  // this->ID = id;
  // this->Name = name;
  // this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid) { this->NodeIDs.push_back(nodeid); }

void Building::print(const Nodes &nodes) {
  for (long long nodeid : NodeIDs) {
    std::cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      std::cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        std::cout << ", is entrance";

      std::cout << std::endl;
    } else {
      std::cout << "**NOT FOUND**" << std::endl;
    }
  } // for
}
