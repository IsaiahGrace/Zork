#include "Room.hpp"

Room::Room(xml_node<char> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  isExit = false;

  while(child) {
    string tagName = child->name();

    if(tagName == "item") items.push_back(child->name());
    else if(tagName == "border") borders.push_back(Border(child));
    else if(tagName == "type") isExit = true; // Only rooms with exits have the <type> tagName

    child = child->next_sibling();
  }
}
