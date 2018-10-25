#include <string>
#include <iostream>
#include "Container.hpp"
#include "rapidxml.hpp"
#include "Base.hpp"
#include "Item.hpp"
using namespace rapidxml;

Container::Container(xml_node<> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout << "Container: " << tagName << std::endl;
    
    if(!tagName.compare("accept")) accept = child->value();
    else if(!tagName.compare("item")) items.push_back(child->value());

    child = child->next_sibling();
  }
}
