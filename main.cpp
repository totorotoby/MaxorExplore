#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "init_states.h"
#include "choice_functions.h"
#include "agent.h"

/*
Program that runs max explore problem.

Parameters:
	
	T - Number of timesteps

	n - Number of states

	V - set of possible rewards (this can come in different forms).
		For now we can make it range that we sample from n times with repatition.
		This is get the effect of m distinct values to be assigned to the n states.

	A evaluation Func - Something to evalute how well we did at aquiring values.

	A Stratgey - How to pick explore or maximize.
				 Really we want to find the stratgey that minimizes some evaluation function.
				 But for now we are just playing around and brute forcing it.


Command line args:

	T
	n
	V as a range
	flag for evaluation function

*/

vector<int> testVector(int samplesNum, vector<int> inputStates, Agent *agent){

	int i;
	int j;
	vector<int> samples;

	for (i = 0 ; i < samplesNum ; i++){
		//cout << "\nOn iteration: " << i <<endl;
		for (j = 0 ; j < agent->choiceVector.size() ; j++){
			//cout << "\n\tOn iteration: " << j <<endl;
			if (agent->choiceVector[j] == 0){
			//	cout << "\texploring!" << endl;
				agent->explore();
			}
			else{
			//	cout << "\tmaximizing!" << endl;
				agent->maximize();
			}
		}
		samples.push_back(agent->totalValue);
		agent->reset(inputStates);
	}

	//agent->remakeVector();
	return samples;
}

int main(int argc, char *argv[]){

	// This section is all to parse the parameters into the correct formats

	int T;
	int n;
	int minValue;
	int maxValue;
	char *funcFlag;

	if(argc != 6){
		printf("The command line arguments were not input properly\n[Number of timesteps][number of states][min value][max value][funcFlag]\n");
		exit(0);
	}

	T = strtol(argv[1], NULL, 10);
	n = strtol(argv[2], NULL, 10);
	minValue = strtol(argv[3], NULL, 10);
	maxValue = strtol(argv[4], NULL, 10);
	funcFlag = argv[5];

	//##########################################################################
	// getting states
	vector<int> states = getStates(n, minValue, maxValue);
	// getting choice vector function
	vec_func vFunc = getVecFunc(funcFlag);
	
	//printSandV(states);
	
	Agent *test = new Agent(states, vFunc, T);

	vector<int> runtest = testVector(1000, states ,test);

	for (int i = 0 ; i<runtest.size() ; i++){
		cout << "\n" << runtest[i] << "\n" << endl;
	}

	delete test;

	


}