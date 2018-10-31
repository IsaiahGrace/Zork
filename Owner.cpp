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


