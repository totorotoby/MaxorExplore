#include <stdlib.h>
#include <iostream>
#include "agent.h"


Agent::Agent(vector<int> inputStates, vec_func makeVector, int T){

		this->T = T;
		this->index = 5;
		this->makeVector = makeVector;
		//this->choiceVector = (int*) malloc(sizeof(int)*T);
		this->choiceVector= this->makeVector(this->index, T);
		this->totalValue = 0;

		
		for (int i = 0; i < inputStates.size() ; i++){
			this->unseen[i] = inputStates[i];
		}

}


void Agent::reset(vector<int> inputStates){

	this->totalValue = 0;

	this->seen.clear();
	this->unseen.clear();

	for (int i = 0; i < inputStates.size() ; i++){
			this->unseen[i] = inputStates[i];
		}

	this->stateLog.clear();

}

void Agent::remakeVector(void){

	this->index = this->index + 1;
	this->choiceVector = this->makeVector(this->index, this->T);

}

int Agent::explore(){

	//needs
	vector<int> values = this->getValues(this->unseen);
	vector<int> states = this->getKeys(this->unseen);
	//print_map(this->unseen);
	
	/*debug
	for (int i = 0 ; i < states.size() ; i++){
		cout << states[i] << " ";
	}
	cout << "\n";
	for (int i = 0 ; i < states.size() ; i++){
		cout << values[i] << " ";
	}
	cout << "\n";
	*/

	int size = states.size();

	int index = rand() % size;
	
	//debug
	//cout << "\t" << index << " " << states[index] << " " << values[index] << endl;

	this->totalValue = this->totalValue + values[index];
	this->stateLog.push_back(states[index]);

	this->seen[states[index]] = values[index];
	this->unseen.erase(states[index]);

}

int Agent::maximize(){

	int max = 0;
	int index = -1;

	vector<int> values = this->getValues(this->seen);
	vector<int> states = this->getKeys(this->seen);

	for (int i = 0 ; i < values.size() ; i++){
			if (values[i] > max){
				max = values[i];
				index = states[i];
				//cout << "\t" << i << " " << index << " " << max << "\n";

			}
		}
	
	//cout<< "\t" << index << " " << max;

	this->stateLog.push_back(index);
	this->totalValue = this->totalValue + max;

	return max;
}

vector<int> Agent::getKeys(unordered_map<int,int> map){

	vector<int> keys;
	keys.reserve(map.size());


	for(auto kv : map) {
    keys.push_back(kv.first); 
	} 

	return keys;

}

vector<int> Agent::getValues(unordered_map<int,int> map){

	vector<int> vals;
	vals.reserve(map.size());

	for(auto kv : map) {
	vals.push_back(kv.second); 
	}

	return vals;

}

template<typename K, typename V>
void print_map(unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}


