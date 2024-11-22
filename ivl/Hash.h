#pragma once
#include<iostream>
#include<vector>

using namespace std;

#ifndef HASH_H
#define HASH_H

class HashMap {
public:

	vector<int> value;
	vector<vector<int>> nodeMap;//
	vector<string> nodeName;//
	vector<int> nodeType;//
	vector<string> endNode;//
	vector<int> nodeFloor;
	vector<string>startNode;//
	int size;//
	int maxFloor;

	void MapCheck() {
		for (int i = 0; i < nodeMap.size(); i++) 
			if (!nodeMap.at(i).empty()) {
				cout << i << ":";
				for (int j = 0; j < nodeMap.at(i).size(); j++)
					cout << nodeMap.at(i).at(j)<<" ";
				cout << endl;
			}
		cout << size << endl;
		for (int i = 0; i < nodeName.size(); i++)
			cout << nodeName.at(i)<<" ";
		cout << endl;
		for (int i = 0; i < nodeType.size(); i++)
			cout << nodeType.at(i) << " ";
		cout << endl;
	}

	int FindIdByName(string str) {
		for (int i = 0; i < size; i++)
			if (str == nodeName.at(i))
				return i;
		return -1;
	}

	void Initialization(vector<string> map,vector<vector<string>> equals,vector<string> output,vector<string> input) {

		startNode = input;
		endNode = output;
		size = map.size();	
		nodeName = map;
		vector<int> vec;

		for (int i = 0; i < size; i++) {
			value.push_back(0);
			nodeFloor.push_back(0);
			nodeType.push_back(0);
			nodeMap.push_back(vec);
		}


		for (int i = 0; i < equals.size(); i++) {

			int t_size = equals.at(i).size();
			int id = FindIdByName(equals.at(i).at(t_size - 2));


			if (equals.at(i).back() == "1")
				nodeType.at(id) = 1;
			else if (equals.at(i).back() == "2")
				nodeType.at(id) = 2;
			else
				nodeType.at(id) = 3;

			for (int j = 0; j < equals.at(i).size() - 2; j++) {
				int temp = FindIdByName(equals.at(i).at(j));
				vec.push_back(temp);
			}
			nodeMap[id] = vec;
			vec.clear();
		}

		NodeFloorInitialization();

	}
private:

	void MaxFloor() {
		int max = -1;
		for (int i = 0; i < nodeFloor.size(); i++)
			if (nodeFloor.at(i) > max)
				max = nodeFloor.at(i);
		maxFloor = max;
	}

	void NodeFloorInitialization() {

		for (int i = 0; i < size; i++)
			nodeFloor.push_back(0);
		for (int i = 0; i < endNode.size(); i++)
			_DFS(FindIdByName(endNode.at(i)));

		MaxFloor();
	}

	int _DFS(int id) {

		int max = -1;
		if (nodeMap.at(id).empty())
			return 0;

		for (int i = 0; i < nodeMap.at(id).size(); i++) {
			int result = _DFS(nodeMap.at(id).at(i));
			if (max < result)
				max = result;
		}

		max++;
		nodeFloor.at(id) = max;
		return max;

	}
};
#endif 
