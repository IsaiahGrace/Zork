#ifndef OWNER_HPP
#define OWNER_HPP

#include <string>
#include <vector>
#include "rapidxml.hpp"
using namespace std;
using namespace rapidxml;


class Owner{
public:
	Owner(xml_node<> *node);
	virtual ~Owner() {};

    vector<string> items; //Items contained in the container

};

#endif
