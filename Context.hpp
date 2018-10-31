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
  Context();
  Context(Room* startingRoom, Inventory* inventory);
  virtual ~Context() {};

  void parseContext();
  Trigger* checkCommandTriggers(string,void*);
  Trigger* checkNonCommandTriggers(void*);

  //you cannot have a vector of references thanks to their immutability
  //so now it's a vector of pointers!
  vector<Trigger*> commandTriggers;
  vector<Trigger*> nonCommandTriggers;

  // currentRoom needs to be a pointer because it will change and refrences cannot be changed
  Room* currentRoom = NULL;
  // I tried to make inventory a refrence, because it never changes.
  // but I can't get the refrence initilization syntax to work at all... So I'ts a pointer.
  Inventory* inventory = NULL;

};

#endif
