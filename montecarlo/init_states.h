#ifndef _INIT_STATES_H
#define _INIT_STATES_H
#include <vector>
using namespace std;

int randNumber(int min, int max);
void makeValues(int *values, int n, int min, int max);
vector<int> getStates(int n, int minValue, int maxValue);
void printSandV(vector<int> states); 
#endif