#include <unordered_map>
#include <vector>
#include "init_states.h"
#include "choice_functions.h"

using namespace std;

template<typename K, typename V>
void print_map(unordered_map<K,V> const &m);
vector<int> getKeys(unordered_map<int,int> map);
vector<int> getValues(unordered_map<int,int> map);
int maxVorS(unordered_map<int,int> map, char flag);

class Agent
{
public:

	// number of timesteps
	int T;
	//the total value accumlated over the time period
	int totalValue;
	// the current choice vector generated by makeVectorfunc
	vector<int> choiceVector;
	//the specfic function that makes the choice vector
	vec_func makeVector;
	//the states that the agent has already been to
	unordered_map<int, int> seen;
	//the states that the agent hasn't been to yet
	unordered_map<int, int> unseen;
	//a log of each state visited with index as time step
	vector<int> stateLog;
	
	Agent(vector<int> inputStates, vec_func makeVector, int T);
	void reset(vector<int> inputStates);
	void remakeVector(int index);
	int explore();
	int maximize();
	void printInfo(void);
	void onlineChoice(int min, int max);

};