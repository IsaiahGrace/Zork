#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Room.hpp"
#include "Inventory.hpp"

using namespace rapidxml;
using namespace std;

class Context {
public:
  Context(Room,Inventory);
  virtual ~Context() {};

  void parseContext();
  Trigger& checkCommandTriggers();
  Trigger& checkNonCommandTriggers();

  vector<Trigger> commandTriggers;
  vector<Trigger> nonCommandTriggers;

  Room currentRoom;
  Inventory currentInventory;

};

#endif
