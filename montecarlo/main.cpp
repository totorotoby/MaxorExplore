#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "init_states.h"
#include "choice_functions.h"
#include "agent.h"

using namespace std;

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

/*
void writeCDFFile(vector<int> y){

	ofstream out("graph.dat");
	vector<int> x;
	int leny = y.size();

	sort(y.begin(),y.end());

	for (int i = 0 ; i < leny ; i++){
		double x = (double) i/leny;
		cout << x << "\n";
		string sy= to_string(y[i]);
		string sx= to_string(x);
		string towrite = sy + "\t" + sx + "\n";
		out << towrite;
	}

	out.close();
}
*/

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
	ofstream out("graph.dat");

	


	
	
	//#################### main monte carlo loop ##################
	
	// it on redraws of value set
	int valIter;
	// index of explore/max switch;
	int vecIter;
	// it on trying same vector
	int exIter;
	// timestep on
	int tIter;
	srand(time(NULL));
	// choice vector function
	vec_func vFunc = getVecFunc(funcFlag);
	//loop over value sets
	for (valIter = 0 ; valIter < 10; valIter++){
		//value set
		vector<int> states = getStates(n, minValue, maxValue);
		Agent *test = new Agent(states, vFunc, T);
		//loop over different choice vectors
		for (vecIter = 1; vecIter < test->choiceVector.size() ; vecIter++){
			//loop over number of simulations on choice vector
			for (exIter = 0 ; exIter < 100 ; exIter++){
				//loop over timesteps
				for (tIter = 0 ; tIter < T ; tIter++){
					if (test->choiceVector[tIter] == 0){
						test->explore();
					}
					else{
						test->maximize();
						}
					}
				string totalValue = to_string(test->totalValue);
				string toWrite = totalValue + ", ";
				out << toWrite;
				test->reset(states);
				//cout << "\t\t" << exIter/4.0 << "\n";
			}
			out << "\n";
			test->remakeVector(vecIter);
			test->printInfo();
			//cout<< "\t" << (double) vecIter/states.size() << "\n";
		}
		out << "\n";
		delete test;
		//cout<< valIter << " " << (double) valIter/3.0 << "\n";
	}


	//writeCDFFile(runtest);


}
