#include "Base.hpp"

Base::Base(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();

    if(tagName == "name") this->name = child->value();
    else if(tagName == "status") this->status = child->value();
    else if(tagName == "description") this->description = child->value();
    else if(tagName == "trigger") triggers.push_back(Trigger(child));

    child = child->next_sibling();
  }
}

Base *Base::search(vector<Base> *bases, string name) {
  for(int i = 0; i < bases->size(); i++) {
    if(name.compare((*bases)[i].name)) return &(*bases)[i];
  }
  return NULL;
}
