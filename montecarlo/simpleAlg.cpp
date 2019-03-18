#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "init_states.h"
#include "choice_functions.h"
#include "agent.h"

using namespace std;


/*
Possible boring solution:

At t=0 explore

for t>0:
    if max(seen) > E(value setting dist):
        maximize
    else:
        explore
*/


int main(int argc, char *argv[]){

	int T = strtol(argv[1], NULL, 10);
	int n = strtol(argv[2], NULL, 10);
	int minValue = strtol(argv[3], NULL, 10);
	int maxValue = strtol(argv[4], NULL, 10);
	int seed = strtol(argv[5], NULL, 10);

	srand(seed);
  
	vector<int> states = getStates(n,minValue, maxValue);

	Agent *agent = new Agent(states, NULL, T);

	//first timestep
	agent->explore();


	for (int i = 0 ; i < 1000 < i++){
		for (int j = 1 ; j < T ; j++){
			agent->onlineChoice(minValue, maxValue);
		}
	}

}  
