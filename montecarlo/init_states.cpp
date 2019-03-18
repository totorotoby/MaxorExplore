#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include "init_states.h"


using namespace std;

int randNumber(int min, int max){
	// returns a random number in  range min to max

	int num = rand() % (max - min + 1) + min;
	return num;
}

void makeValues(int *values, int n, int min, int max){
//fills the values array with random numbers for each state from min to max

	//seeding random number generator with the time
	//struct timeval tp;
	//gettimeofday(&tp, NULL);
	//long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	// looping through and adding random numbers
	for (int i = 0 ; i < n ; i++){
		values[i] = randNumber(min, max);
	}
}

vector<int> getStates(int n, int minValue, int maxValue){

	//creating list of values, the index of a value can be the number state
	int *Values = (int*) malloc(sizeof(int)*n);
	makeValues(Values, n, minValue, maxValue);	
	int numStates = sizeof(Values) / sizeof(Values[0]);

	vector<int> valueTable;

	for (int i = 0 ; i < n ; i++){
		valueTable.push_back(Values[i]);
	}

	free(Values);
	return valueTable;
}

void printSandV(vector<int> states){
	
	printf("%-10s%-10s\n", "State", "Value");

	for (int i = 0; i < states.size() ; i++){
		printf("%-10d%-10d\n", i, states[i]);
	}
}
