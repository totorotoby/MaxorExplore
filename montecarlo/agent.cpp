#include <stdlib.h>
#include <iostream>
#include "agent.h"

Agent::Agent(vector<int> inputStates, vec_func makeVector, int T){

		this->T = T;
		this->makeVector = makeVector;
		//this->choiceVector = (int*) malloc(sizeof(int)*T);
		if (makeVector != NULL){
		this->choiceVector= this->makeVector(1, T);
		}
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

void Agent::remakeVector(int index){

	this->choiceVector = this->makeVector(index, this->T);

}

int Agent::explore(){

	//needs
	vector<int> values = getValues(this->unseen);
	vector<int> states = getKeys(this->unseen);
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
	
	//cout<< "\t" << index << " " << max;
	int index = maxVorS(this->seen, 'S');
	int max = maxVorS(this->seen, 'V');

	this->stateLog.push_back(index);
	this->totalValue = this->totalValue + max;

	return max;
}


void Agent::onlineChoice(int min, int max){

	double seen_max = (double) maxVorS(this->seen, 'V');
	double mean = (max + min) / 2;

	if (seen_max > mean){
		this->maximize();
	}
	else{
		this->explore();
	}


}

vector<int> getKeys(unordered_map<int,int> map){

	vector<int> keys;
	keys.reserve(map.size());

	for(auto kv : map) {
    keys.push_back(kv.first); 
	} 

	return keys;

}

vector<int> getValues(unordered_map<int,int> map){

	vector<int> vals;
	vals.reserve(map.size());

	for(auto kv : map) {
	vals.push_back(kv.second); 
	}

	return vals;

}

void Agent::printInfo(void){

	cout << "The Current States and Assosiated values are:\n";
	print_map(this->unseen);
	cout << "\n\nThe Current Decision Vector is:\n";
	for (int i = 0 ; i < this->choiceVector.size() ; i++){
		cout << choiceVector[i] << ", ";
	}
	cout << "\n\n\n\n";

}


template<typename K, typename V>
void print_map(unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        cout << pair.first << " -> " << pair.second << "\n";
    }
}

int maxVorS(unordered_map<int,int> map, char flag){

	int toreturn = 0;
	int index = -1;

	vector<int> values = getValues(map);
	vector<int> states = getKeys(map);

	for (int i = 0 ; i < values.size() ; i++){
			if (values[i] > toreturn){
				if (flag == 'V'){
					toreturn = values[i];
				}
				else{
				toreturn = states[i];
				index = states[i];
				}
			}
		}

	if (flag == 'S'){
		toreturn = index;
	}
	
	return toreturn;
}