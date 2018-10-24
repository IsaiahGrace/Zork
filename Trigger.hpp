#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Condition.hpp"
using namespace rapidxml;
using namespace std;

class Trigger {
public:
	Trigger(xml_node<> *node);
	virtual ~Trigger() {};
	//take 3
	string type = NULL;
	string command;
	vector<Condition> conditions;
	string print;
};

#endif
