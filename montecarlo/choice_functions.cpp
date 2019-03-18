#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#include "choice_functions.h"

vec_func getVecFunc(char *funcFlag){
	
	if (strcmp(funcFlag, "S") == 0){
		vec_func func;
		func = funcS;
		return func;
	}
}

vector<int> funcS(int index, int T){

	int i;
	
	vector<int> cVec;

	for (i = 0 ; i < index ; i++){
		cVec.push_back(0);
	}
	for (i = index ; i < T ; i++){
		cVec.push_back(1);
	}

	return cVec;
}