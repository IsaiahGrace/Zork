#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Base.hpp"
#include "Item.hpp"

class Container : public Base {
public:
	Container() {};
	Container(xml_node<> *node);
	virtual ~Container() {};

	static Container *search(vector<Container> *containers, string name);
	
	string accept; //The container unlocker
	vector<string> items; //Items contained in the container
};

#endif
