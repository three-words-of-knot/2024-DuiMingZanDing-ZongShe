#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include "MyMethod.h"

using namespace std;

int _DFS(vector<vector<int>> map_node,int node_id,vector<int> &floor) {
	vector<int> Temp;
	for (int i = 0; i < map_node.size(); i++) {
		if (map_node[i][node_id] == 1 || map_node[i][node_id] == 2) {
			int temp = _DFS(map_node, i, floor);
			Temp.push_back(temp);
		}
	}
	int max = -1;
	for (int i = 0; i < Temp.size(); i++)
		if (max < Temp.at(i))
			max = Temp.at(i);
	max++;
	floor[node_id] = max;
	return max;
}

void AFAP(vector<vector<int>> map_node,vector<char> map_name,vector<int> end) {
	vector<int> floor;
	for (int i = 0; i < map_node.size(); i++)
		floor.push_back(0);
	for (int i = 0; i < end.size(); i++)
		_DFS(map_node, end[i], floor);
	for (int i = 0; i < floor.size(); i++)
		printf("%d ", floor.at(i));
}
/*从终点递归到起点，然后起点开始向上传数据，
* 如果有多个就比较最大者，然后加一接着传，最后的顺序在floor的向量中储存，后续这里添加打印功能或者输出功能
*/