/*osm.h*/

//
// Functions for working with an Open Street Map file.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 
// References:
// 
// TinyXML: 
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
// 
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#pragma once

#include "tinyxml2.h"
#include <iostream>



//
// Helper functions:
//
bool osmLoadMapFile(std::string filename, tinyxml2::XMLDocument& xmldoc);
bool osmContainsKeyValue(tinyxml2::XMLElement* e, std::string key, std::string value);
std::string osmGetKeyValue(tinyxml2::XMLElement* e, std::string key);
