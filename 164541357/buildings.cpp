/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"

//
// readMapBuildings
//
// Given an XML document, reads through the document and
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(tinyxml2::XMLDocument &xmldoc) {
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
    if (osmContainsKeyValue(way, "building", "university")) {
      std::string name = osmGetKeyValue(way, "name");

      std::string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " +
                               osmGetKeyValue(way, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);

      tinyxml2::XMLElement *nd = way->FirstChildElement("nd");

      while (nd != nullptr) {
        const tinyxml2::XMLAttribute *ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        B.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapBuildings.push_back(B);
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
int Buildings::getNumMapBuildings() { return (int)this->MapBuildings.size(); }

void Buildings::print() {
  for (Building B : MapBuildings) {
    std::cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << std::endl;
  }
}

std::vector<Footway> intersections(const Building &B,
                                   const Footways &footways) {
  std::vector<Footway> intersection_footways;

  std::vector<long long> bs = B.NodeIDs;
  std::sort(bs.begin(), bs.end());

  for (const auto &footway : footways.MapFootways) {

    std::vector<long long> ft = footway.NodeIDs;
    std::sort(ft.begin(), ft.end());

    std::vector<long long> intersections;

    std::set_intersection(bs.begin(), bs.end(), ft.begin(), ft.end(),
                          back_inserter(intersections));

    if (intersections.size()) {
      intersection_footways.push_back(footway);
    }
  }
  return intersection_footways;
}

void print_footways(std::vector<Footway>&& intersection_footways) {
  if (intersection_footways.size() == 0) {
    std::cout << " None" << std::endl;
  } else {
    std::sort(intersection_footways.begin(), intersection_footways.end());
    intersection_footways.erase(
        std::unique(intersection_footways.begin(), intersection_footways.end()),
        intersection_footways.end());
    for (const auto &footway : intersection_footways) {
      std::cout << " Footway " << footway.ID << std::endl;
    }
  }
}

void Buildings::findAndPrint(const std::string &name, const Nodes &nodes,
                             const Footways &footways) {
  //
  // find every building that contains this name:
  //
  for (Building B : MapBuildings) {
    if (B.Name.find(name) != std::string::npos) {
      // contains name:
      std::cout << B.Name << std::endl;
      std::cout << "Address: " << B.StreetAddress << std::endl;
      std::cout << "Building ID: " << B.ID << std::endl;
      std::cout << "Nodes:" << std::endl;
      B.print(nodes);
      std::cout << "Footways that intersect:" << std::endl;
      print_footways(intersections(B, footways));
    }
  }
}
