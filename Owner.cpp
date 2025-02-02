#include "rapidxml.hpp"
#include "Owner.hpp"
#include "Map.hpp"
#include <string>
#include <vector>
#include <iostream>

Owner::Owner(){}
Owner::Owner(xml_node<> *node,void* mymap){

	  Map* mapptr = static_cast<Map*>(mymap);
	  xml_node<> *child = node->first_node();

	  while(child) {
	    string tagName = child->name();
#ifndef RELEASE
	    std::cout << "Owner: " << tagName << std::endl;
#endif

	    if(tagName == "item"){
	    	for(unsigned int i = 0; i < mapptr->items.size() ;i++){

	      		if(mapptr->items[i].name == child->value()){
#ifndef RELEASE
	      			std::cout << "Item:" << mapptr->items[i].name << " added to container" << std::endl;
#endif
	       			items.push_back(&mapptr->items[i]);
	      		}
	    	}
	    }


	    child = child->next_sibling();
	  }


}

Item* Owner::GetItem(string itemName){
	  for (unsigned int i = 0; i < items.size(); i++) {
	    if(items[i]->name == itemName){
	    	return items[i];
	    }
	  }
	  return NULL; // Item not found
}
