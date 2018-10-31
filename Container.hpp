#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Base.hpp"
#include "Item.hpp"
#include "Owner.hpp"

class Container : public Base, public Owner {
public:
  Container(xml_node<> *node,void* mymap);
  virtual ~Container() {};
	
  string accept; //The container unlocker
  //vector<string> items; //Items contained in the container
};

#endif
