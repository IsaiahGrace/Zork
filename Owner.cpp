#include "rapidxml.hpp"
#include "Owner.hpp"
#include <string>
#include <vector>
#include <iostream>


Owner::Owner(xml_node<> *node){

	  xml_node<> *child = node->first_node();

	  while(child) {
	    string tagName = child->name();
	    std::cout << "Owner: " << tagName << std::endl;

	    if(!tagName.compare("item")) items.push_back(child->value());

	    child = child->next_sibling();
	  }


}

bool Owner::FindItem(string itemname){
	  for (unsigned int i = 0; i < items.size(); i++) {
	    if(items[i] == itemname) return true;
	  }
	  return false; // Item not found
}
