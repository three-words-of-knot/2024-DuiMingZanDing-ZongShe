#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>

using namespace std;

void _DPS(vector<vector<int>> map_node, vector<char> map_name, vector<int>floor,int deep,int node) {

}

void AFAP(vector<vector<int>> map_node,vector<char> map_name) {
	vector<int> head;
	for (int i = 0; i < map_node.size(); i++) {
		bool flag=true;
		for (int j = 0; j < map_node[i].size(); j++) {
			if (map_node[i][j] == 1 || map_node[i][j] == 2)
				flag = false;
		}
		if (flag)
			head.push_back(i);
	}
	vector<int>floor;
	for (int i = 0; i < map_node.size(); i++)
		floor.push_back(0);
}