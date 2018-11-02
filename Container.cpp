#include <string>
#include <iostream>
#include "Container.hpp"
#include "rapidxml.hpp"
#include "Base.hpp"
#include "Item.hpp"
#include "Owner.hpp"
using namespace rapidxml;

Container::Container(xml_node<> *node,void* mymap) : Base::Base(node), Owner::Owner(node,mymap) {
  xml_node<> *child = node->first_node();
  //status = "locked";
  while(child) {
    string tagName = child->name();
    std::cout << "Container: " << tagName << std::endl;
    
    if(!tagName.compare("accept")) accept = child->value();
    //else if(!tagName.compare("item")) items.push_back(child->value());

    child = child->next_sibling();
  }
}

Item* Container::GetItem(string itemName) {
	//if(status == "locked"){
	//	return NULL;
	//}

  for (unsigned int i = 0; i < items.size(); i++) {
    if(items[i]->name == itemName) return items[i];
  }
  return NULL; // Item not found
}
