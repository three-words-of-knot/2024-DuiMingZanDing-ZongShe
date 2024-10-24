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
	int size;

	int FindInNodeMap(int x, int y) {
		int _temp = x * size + y - 1;
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

	void Initialization(vector<char> map,vector<vector<string>> node) {


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
	}
private:

	void ChangeNodeMap(int x, int y, int t) {
		int _temp = x * size + y - 1;
		nodeMap.at(_temp) = t;
	}

	void ChangeNodeType(int x, int t) {
		nodeType.at(x) = t;
	}
};
#endif 
