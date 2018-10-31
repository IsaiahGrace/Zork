#ifndef OWNER_HPP
#define OWNER_HPP

#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Item.hpp"
using namespace std;
using namespace rapidxml;


class Owner{
public:
	Owner(xml_node<> *node,void* mapptr);
	virtual ~Owner() {};

	Item* GetItem(string);
    vector<Item> items; //Items contained in the container

};

#endif
