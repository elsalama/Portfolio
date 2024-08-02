/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"

//
// readMapBuildings
//
// Given an XML document, reads through the document and
// stores all the buildings into the given vector.
//
void Footways::readMapFootways(tinyxml2::XMLDocument &xmldoc) {
  tinyxml2::XMLElement *osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  tinyxml2::XMLElement *way = osm->FirstChildElement("way");

  while (way != nullptr) {
    const tinyxml2::XMLAttribute *attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(way, "highway", "footway") ||
        osmContainsKeyValue(way, "area:highway", "footway")) {

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Footway F(id);

      tinyxml2::XMLElement *nd = way->FirstChildElement("nd");

      while (nd != nullptr) {
        const tinyxml2::XMLAttribute *ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        F.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapFootways.push_back(F);
    } // if

    way = way->NextSiblingElement("way");
  } // while

  //
  // done:
  //
}

//
// accessors / getters
//
int Footways::getNumMapFootways() { return (int)this->MapFootways.size(); }

/*
void Footways::print() {
  for (Building B : MapBuildings) {
    std::cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << std::endl;
  }
}

void Footways::findAndPrint(const std::string& name,const Nodes& nodes){
   //
      // find every building that contains this name:
      //
      for (Building B : MapBuildings) {
        if (B.Name.find(name) != std::string::npos) { // contains name:

          std::cout << B.Name << std::endl;
          std::cout << "Address: " << B.StreetAddress << std::endl;
          std::cout << "Building ID: " << B.ID << std::endl;

          std::cout << "Nodes:" << std::endl;
          B.print(nodes);
        }
      }
}
*/
