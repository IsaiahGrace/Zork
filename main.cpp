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
  Inventory playerInventory;
  // Context
  Room* entranceRoom = map.getRoom("Entrance");
  Context gameContext(entranceRoom, &playerInventory);
  // ******************************
  // Start the Finite state Machine
  // ******************************


  while(1){
	  //get current context
	  gameContext.parseContext();

	  //check context for active noncommand triggers


  }

  /*
   * while(1):
   *
   * 	#check context for active triggers
   * 	if trigger condition is met:
   * 		#execute trigger
   *
   * 	else:
   * 		#scan command
   *		command must be parsed at this point and placed into a string
   *
   *
   * 		if context.checkCommandTriggers(string):
   * 			#execute override command
   * 		else:
   * 			#execute regular command by calling execute(string)
   *
   *
   */

  // *************************
  // cleanup after end of game
  // *************************
  // Free memory used

  return EXIT_SUCCESS;
}
