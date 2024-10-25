#pragma once
#include<iostream>
#include<vector>

using namespace std;

#ifndef HASH_H
#define HASH_H

class HashMap {
public:

	vector<int> nodeMap;
	vector<char> nodeName;
	vector<int> nodeType;
	vector<char> endNode;
	vector<int> nodeFloor;
	vector<char>startNode;
	int size;

	int FindInNodeMap(int x, int y) {
		int _temp = x * size + y;
		return nodeMap.at(_temp);
	}

	char FindInNodeName(int x) {
		return nodeName.at(x);
	}

	int FindInNodeType(int x) {
		return nodeType.at(x);
	}

	int FindName(char target) {
		for (int i = 0; i < nodeName.size(); i++)
			if (nodeName.at(i) == target)
				return i;
		return -1;
	}

	void Initialization(vector<char> map,vector<vector<string>> node,vector<char> _output,vector<char> _input) {

		startNode = _input;
		endNode = _output;
		size = map.size();	
		nodeName = map;
		for (int i = 0; i < map.size(); i++) {
			nodeType.push_back(0);
			for (int j = 0; j < map.size(); j++)
				nodeMap.push_back(0);
		}

		for (int i = 0; i < node.size(); i++) {
		    string _nodeline;
			for (int j = 7; j < node.at(i).at(0).size(); j += 2)
				_nodeline.push_back(node.at(i).at(0).at(j));
			if (node.at(i).at(1).at(0) == '0') {
				ChangeNodeMap(FindName(_nodeline.at(0)), FindName(_nodeline.at(1)), 1);
				ChangeNodeType(FindName(_nodeline.back()), 1);
			}
			else if (node.at(i).size() > 3) {
				for (int j = 0; j < _nodeline.size() - 1; j++)
					ChangeNodeMap(FindName(_nodeline.at(j)), FindName(_nodeline.back()), 2);
				ChangeNodeType(FindName(_nodeline.back()), 2);
			}
			else {
				for (int j = 0; j < _nodeline.size() - 1; j++)
					ChangeNodeMap(FindName(_nodeline.at(j)), FindName(_nodeline.back()), 3);
				ChangeNodeType(FindName(_nodeline.back()), 3);
			}
		}

		NodeFloorInitialization();

	}
private:

	void ChangeNodeMap(int x, int y, int t) {

		int _temp = x * size + y;
		nodeMap.at(_temp) = t;

	}

	void ChangeNodeType(int x, int t) {

		nodeType.at(x) = t;

	}

	bool FindInStartNode(int target) {
		char _temp = FindInNodeName(target);
		for (int i = 0; i < startNode.size(); i++)
			if (_temp == startNode.at(i))
				return true;
		return false;
	}

	void NodeFloorInitialization() {

		for (int i = 0; i < size; i++)
			nodeFloor.push_back(0);
		for (int i = 0; i < endNode.size(); i++)
			_DFS(FindName(endNode.at(i)));

	}

	int _DFS(int _last) {
		if (FindInStartNode(_last))
			return 0;
		int max = -1;
		for (int i = 0; i < size; i++) {
			int result = FindInNodeMap(i, _last);
			if (result != 0) {
				int _temp = _DFS(i);
				if (_temp > max)
					max = _temp;
			}
		}
		max++;
		nodeFloor.at(_last) = max;
		return max;

	}
};
#endif 
