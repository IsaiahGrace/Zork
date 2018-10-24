#include "Map.hpp"
#include <iostream>

Map::Map(FILE *fptr) {
  //Determine the .xml file size
  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  rewind(fptr);

  //Create a character array to hold the .xml file
  char *xml = (char *) malloc(size * sizeof(char));

  //read the contents of the xml file into the char array
  fread(xml, size, 1, fptr);

  //Parse the character array
  xml_document<> doc;
  doc.parse<0>(xml);

  //For each of the children of the Map node:
  xml_node<> *node = doc.first_node()->first_node();

  while(node) {
    string name = node->name();
    std::cout << name << std::endl;

    if(name == "room") rooms.push_back(Room(node));
    else if(name == "item") items.push_back(Item(node));
    else if(name == "container") containers.push_back(Container(node));
    else if(name == "creature") creatures.push_back(Creature(node));

    node = node->next_sibling();
  }
}
