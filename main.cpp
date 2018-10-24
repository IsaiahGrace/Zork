#include <iostream>
#include <string>
#include "Map.hpp"

using namespace std;

Base *search(vector<Base> *bases, string name) {
  for(unsigned int i = 0; i < bases->size(); i++) {
    if(name.compare((*bases)[i].name)) return &(*bases)[i];
  }
  return NULL;
}

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


  // ******************************
  // Start the Finite state Machine
  // ******************************
  // Get command from the user
  
  // Check if command is overriden by a trigger
  
  // Execute command if not overridden
  
  // Check if command activates a trigger
  
  // Execute trigger
  
  /*
   * while(1):
   *
   * 	#check context for active triggers
   * 	if trigger condition is met:
   * 		#execute trigger
   *
   * 	else:
   * 		#scan command
   *
   * 		if context has overrides for command:
   * 			#execute override command
   * 		else:
   * 			#execute regular command
   *
   */

  // *************************
  // cleanup after end of game
  // *************************
  // Free memory used

  return EXIT_SUCCESS;
}
