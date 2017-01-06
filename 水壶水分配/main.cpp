#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int STRING[3] = {8,5,3};
map<int, int> father;

int Adj(int mod, vector<int>& next_state, vector<int>& keyTable, bool modify_key){
	int mode[3];
	mode[0] = mod % 10;
	mode[1] = (mod / 10) % 10;
	mode[2] = mod / 100;

	//判断下一个可能的状态
	int water_valum;
	int loops = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(j == i)
				continue;
			water_valum = min(mode[i], STRING[j] - mode[j]);//要么把倒出水的杯子倒空，要么把倒入水的杯子装满

			if(water_valum != 0){
				int next[3];
				//倒水动作
				next[i] = mode[i] - water_valum;
				next[j] = mode[j] + water_valum;
				for(int k = 0; k < 3; k++){
					if(k != i && k != j)
						next[k] = mode[k];
				}
				int number = next[0] + next[1] * 10 + next[2] * 100;
				vector<int>::iterator it = find(keyTable.begin(), keyTable.end(), number);
				if(it == keyTable.end()){
					next_state.push_back(number);
					father[number] = mod;
					if(modify_key){
						keyTable.push_back(number);
					}
					loops++;
				}
			}
		}
	}
	return loops;
}
int BFS(int mod, vector<int>& keyTable){
	queue<int> myQ;
	myQ.push(mod);

	while(!myQ.empty()){
		int curState = myQ.front();
		myQ.pop();
		vector<int> next_state;
		int loops = Adj(curState, next_state, keyTable, true);

		for(int i = 0; i < loops; i++){
			int next[3];
			next[0] = next_state[i] % 10;
			next[1] = (next_state[i] / 10) % 10;
			next[2] = next_state[i] / 100;

			if(next[0] == 4 || next[1] == 4 || next[2] == 4){
				return next_state[i];
			}

			myQ.push(next_state[i]);
		}
	}
}
int main(){
	//已经查找过的节点值放入一个vector中，避免重复
	vector<int> keyTable;
	int ini_state = 8;

	vector<int> path;
	string result = "";
	keyTable.push_back(ini_state);
	int end_state = BFS(ini_state, keyTable);
	path.push_back(end_state);
	while(father.find(end_state) != father.end()){
		end_state = father[end_state];
		path.push_back(end_state);
	}

	for(int i = path.size() - 1; i >= 0; i--){
		if(i != 0)
			cout<<path[i]<<"->";
		else
			cout<<path[i];
	}
	cout<<endl;
	return 0;
}