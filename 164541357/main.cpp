/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include <iostream>
#include <string>

#include "footways.h"
#include "building.h"
#include "buildings.h"
#include "footway.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

//
// main
//
int main() {
  tinyxml2::XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;

  std::cout << "** NU open street map **" << std::endl;

  std::string filename;

  std::cout << std::endl;
  std::cout << "Enter map filename> " << std::endl;
  getline(std::cin, filename);

  //
  // 1. load XML-based map file
  //
  if (!osmLoadMapFile(filename, xmldoc)) {
    // failed, error message already output
    return 0;
  }

  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // NOTE: let's sort so we can use binary search when we need
  // to lookup nodes.
  //
  nodes.sortByID();

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways, which are the walking paths:
  //
  //
  footways.readMapFootways(xmldoc);
  //

  //
  // 5. stats
  //
  std::cout << "# of nodes: " << nodes.getNumMapNodes() << std::endl;
  std::cout << "# of buildings: " << buildings.getNumMapBuildings()
            << std::endl;
  std::cout << "# of footways: " << footways.getNumMapFootways()
            << std::endl;
  //
  // TODO
  //

  //
  // now let the user for search for 1 or more buildings:
  //
  while (true) {
    std::string name;

    std::cout << std::endl;
    std::cout << "Enter building name (partial or complete), or * to list, or "
                 "$ to end> "
              << std::endl;

    getline(std::cin, name);

    if (name == "$") {
      break;
    } else if (name == "*") {
      buildings.print();
    } else {
     buildings.findAndPrint(name, nodes, footways);
    } // else

  } // while

  //
  // done:
  //
  std::cout << std::endl;
  std::cout << "** Done  **" << std::endl;
  std::cout << "# of calls to getID(): " << Node::getCallsToGetID()
            << std::endl;
  std::cout << "# of Nodes created: " << Node::getCreated() << std::endl;
  std::cout << "# of Nodes copied: " << Node::getCopied() << std::endl;
  std::cout << std::endl;

  return 0;
}
