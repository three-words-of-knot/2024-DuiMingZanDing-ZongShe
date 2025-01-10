#pragma once
#include<iostream>
#include<vector>

using namespace std;

#ifndef HASH_H
#define HASH_H

class HashMap {
public:

	vector<string> startNode;
	vector<string> endNode;
	vector<string> nodeName;
	vector<vector<int>> nodeMap;

	vector<int> nodeType;//0为非门，1为或门，2为与门
	vector<int> delay;
	vector<vector<int>> doorList;
	vector<int> usableNode;
	vector<vector<int>> nodeList;

	int size;

	int FindIdByName(string str) {
		for (int i = 0; i < size; i++)
			if (str == nodeName.at(i))
				return i;
		return -1;
	}

	void DelayTime() {

		int temp_1, temp_2, temp_3;
		cout<<"请按与、或、非门的顺序输入所需要的时间(例：1 1 1)：";
		cin >> temp_1 >> temp_2 >> temp_3;
		delay.push_back(temp_3);
		delay.push_back(temp_2);
		delay.push_back(temp_1);
		cout << "请输入与、或、非门的数量：";
		cin >> temp_1 >> temp_2 >> temp_3;
		DoorListInitialize(temp_3, temp_2, temp_1);

	}

	void Update() {

		for (int i = 0; i < size; i++) {

			if (usableNode.at(i)!=0)
				continue;

			bool flag = true;
			for (int j = 0; j < nodeMap.at(i).size(); j++)
				if (usableNode.at(nodeMap.at(i).at(j)) != 1)
					flag = false;

			if (flag)
				usableNode.at(i) = 2;
		}

	}

	void Unupdate() {

		for (int i = 0; i < size; i++) {
			if (usableNode.at(i) != 1)
				continue;

			for (int j = 0; j < nodeMap.at(i).size(); j++) {
				int id = nodeMap.at(i).at(j);
				if(usableNode.at(id)==0)
					if(CheckOut(id))
						usableNode.at(id) = 2;
				if (nodeMap.at(id).size() == 0)
					usableNode.at(id) = 1;
			}

		}	

	}

	void ClearNode(vector<int> &temp) {
		for (int i = 0; i < 3; i++) 
			for (int j = 0; j < size; j++) {
				bool flag = true;
				if (nodeType.at(j) == i && usableNode.at(j) == 2) {

					for (int k = 0; k < doorList.at(i).size(); k++)
						if (doorList.at(i).at(k) == 0) {
							doorList.at(i).at(k) = delay.at(i);
							flag = false;
							break;
						}	
					if (flag)
						break;
					usableNode.at(j) = -1;
					nodeList.at(i).push_back(j);
					temp.push_back(j);
				}
			}
	}

	void Refresh() {

		for (int i = 0; i < doorList.size(); i++)
			for (int j = 0; j < doorList.at(i).size(); j++) {
				int temp = doorList.at(i).at(j);
				if ( temp > 0) {
					doorList.at(i).at(j)--;
					temp--;
					if (temp == 0) {
						int id = nodeList.at(i).front();
						usableNode.at(id) = 1;
						nodeList.at(i).erase(nodeList.at(i).begin());
					}
				}
			}
	
	}

	void Clear() {
		for (int i = 0; i < usableNode.size(); i++)
			usableNode.at(i) = 0;
		UsableNodeInitialize();
	}

	bool ListCheck() {
		bool flag = true;
		for (int i = 0; i < size; i++)
			if (usableNode.at(i) != 1)
				flag = false;
		return flag;
	}

	void Initialization(vector<string> map,vector<vector<string>> equals,vector<string> output,vector<string> input) {

		startNode = input;
		endNode = output;
		size = map.size();	
		nodeName = map;
		vector<int> vec;

		for (int i = 0; i < size; i++) {
			nodeType.push_back(-1);
			nodeMap.push_back(vec);
			usableNode.push_back(0);
		}

		for (int i = 0; i < equals.size(); i++) {

			int temp = equals.at(i).size();
			int id = FindIdByName(equals.at(i).at(temp - 2));

			if (equals.at(i).back() == "1")
				nodeType.at(id) = 1;
			else if (equals.at(i).back() == "2")
				nodeType.at(id) = 2;
			else
				nodeType.at(id) = 0;

			for (int j = 0; j < temp - 2; j++) {
				int res	= FindIdByName(equals.at(i).at(j));
				vec.push_back(res);
			}
			nodeMap[id] = vec;
			vec.clear();
		}

		UsableNodeInitialize();
		
	}

	void UsableNodeUninitialize() {
		for (int i = 0; i < size; i++)
			usableNode.at(i) = 0;
		for (int i = 0; i < endNode.size(); i++)
			usableNode.at(FindIdByName(endNode.at(i))) = 2;
	}

	void DelayTime(int NO, int AND,int OR) {
		int temp_1, temp_2, temp_3;
		cout << "请按与、或、非门的顺序输入所需要的时间(例：1 1 1)：";
		cin >> temp_1 >> temp_2 >> temp_3;
		delay.push_back(temp_3);
		delay.push_back(temp_2);
		delay.push_back(temp_1);

		DoorListInitialize(NO, AND, OR);

	}
	void DelayTime(int NO, int AND, int OR,int t1,int t2,int t3) {

		delay.push_back(t3);
		delay.push_back(t2);
		delay.push_back(t1);

		DoorListInitialize(NO, AND, OR);
	}
private:

	bool CheckOut(int id) {
		bool flag = true;
		for (int i = 0; i < size; i++) 
			for (int j = 0; j < nodeMap.at(i).size(); j++)
				if (nodeMap.at(i).at(j) == id&&usableNode.at(i)!=1)
					flag = false;
		return flag;
	}

	void UsableNodeInitialize() {
		for (int i = 0; i < startNode.size(); i++)
			usableNode.at(FindIdByName(startNode.at(i))) = 1;
	}

	void DoorListInitialize(int NO, int OR, int AND) {

		vector<int> temp;
		vector<int> temp_1(NO);
		vector<int> temp_2(OR);
		vector<int> temp_3(AND);
		doorList.push_back(temp_1);
		doorList.push_back(temp_2);
		doorList.push_back(temp_3);
		nodeList.push_back(temp);
		nodeList.push_back(temp);
		nodeList.push_back(temp);

	}
};
#endif;
