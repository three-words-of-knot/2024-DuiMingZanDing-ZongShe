#pragma once
#include<vector>
using namespace std;
#ifndef INFO_H
#define INFO_H

class Info
{
public:
	vector<int> doorCost;
	vector<vector<int>> doorInfo;
	vector<int> saveLoad;
	//”ÎªÚ∑«
	void Initialization(int OR, int AND, int NO,int orNum,int andNum,int noNum) {
		doorCost.push_back(AND);
		doorCost.push_back(OR);
		doorCost.push_back(NO);
		vector<int> vec1(orNum,0);
		vector<int> vec2(andNum,0);
		vector<int> vec3(noNum, 0);
		doorInfo.push_back(vec2);
		doorInfo.push_back(vec1);
		doorInfo.push_back(vec3);
	}

	int CheckDoor(int type) {

		for (int i = 0; i < doorInfo.at(type).size(); i++)
			if (doorInfo.at(type).at(i) == 0) 
				return i;
		return -1;

	}

	void UseDoor(int type, int id,int node) {
		doorInfo.at(type).at(id) = doorCost.at(type);
		saveLoad.push_back(node);
	}

	void Clear(vector<int> &mapper) {
		for (int i = 0; i < doorInfo.size(); i++)
			for (int j = 0; j < doorInfo.at(i).size(); j++)
				if (doorInfo.at(i).at(j) > 0) {
					doorInfo.at(i).at(j) = doorInfo.at(i).at(j) - 1;
					if (doorInfo.at(i).at(j) == 0)
						_push(mapper);
				}

	}

	void Check() {
		for (int i = 0; i < doorInfo.at(0).size(); i++)
			cout << doorInfo.at(0).at(i);
		cout << endl;
	}
private:
	void _push(vector<int> &mapper) {
		int id = saveLoad.front();
		saveLoad.erase(saveLoad.begin());
		mapper.at(id) = 1;
	}

};
#endif