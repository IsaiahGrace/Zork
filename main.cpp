#include <iostream>
#include <string>
#include "Map.hpp"
#include "Inventory.hpp"
#include "Context.hpp"

using namespace std;

// Game Commands
// n,s,e,w -- Movement
// i -- prints inventory
// take(item) -- changes item ownership from room or container to inventory.

int main(int argc, char **argv) {
  // main method broken down into tasks
  // 1. Initilization of the game
  // 2. Finite State Machine (Running the game)
  // 3. Cleanup after end of game

  // ******************
  // Game Initilization
  // ******************
  if(argc != 2) {
    cout << "Error, please specify one .xml map file (argc != 2)" << endl;
    return EXIT_FAILURE;
  }
  FILE *fptr = fopen(argv[1], "r");
  if(fptr == NULL) {
    cout << "Error, fopen failed to find .xml file (fptr == NULL)" << endl;
    return EXIT_FAILURE;
  }


  // Construct the Map object
  Map map(fptr);
  fclose(fptr);

  // Create Player variables

  // Context

  // ******************************
  // Start the Finite state Machine
  // ******************************

  try {
    while(1){
      //get current context
      map.gameContext.parseContext();

      //check context for active noncommand triggers
      Trigger* commandTrigger = map.gameContext.checkNonCommandTriggers(&map);
      if(commandTrigger != NULL){
	//TODO: execute trigger
      }
      else{
	//parse the command line
	string command;
	cout<< "Waiting for command: ";
	getline(cin,command);

	Trigger* nonCommandTrigger = map.gameContext.checkCommandTriggers(command,&map);
	if(nonCommandTrigger != NULL){
	  //TODO: execute trigger
	}
	else{
	  map.parseAction(command);
	  //parseAction should call the action func
	}
      }
    }
  }
  catch (int i) {
    std::cout << "Game Over" << std::endl;
  }
  return EXIT_SUCCESS;
}
