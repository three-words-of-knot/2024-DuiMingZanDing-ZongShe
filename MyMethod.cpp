#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include "MyMethod.h"

using namespace std;

void _printline() {
	printf("\n");
	for (int i = 0; i < 20; i++)
		printf("-");
	printf("\n");
}

vector<int> _Clear(vector<vector<int>> map_node) {
	vector<int> _temp;
	for (int i = 0; i < map_node.size(); i++) {
		bool _flag = false;
		bool _flag2 = false;
		for (int j = 0; j < map_node.size(); j++) {
			if (map_node[j][i] == 2) {
				_flag2 = true;
				_temp.push_back(2);
				break;
			}
			if (map_node[j][i] == 1)
				if (_flag) {
					_flag2 = true;
					_flag = false;
					_temp.push_back(1);
					break;
				}
				else
					_flag = true;
		}
		if (_flag)
			_temp.push_back(3);
		else if(!_flag2)
			_temp.push_back(0);
	}
	return _temp;
}

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

	_printline();
	cout<<"AFAP结果：" << endl;
	for (int i = 0; i < 20; i++) {
		bool flag = true;
		printf("第%d循环中，完成的节点有", i);
		for (int j = 0; j < floor.size(); j++) 
			if (floor.at(j) == i) {
				flag = false;
				printf("%c ", map_name.at(j));
			}
		if (flag) {
			printf("0个，结束循环\n");
			break;
		}
		printf("\n");
	}
	_printline();

}
/*从终点递归到起点，然后起点开始向上传数据，
* 如果有多个就比较最大者，然后加一接着传，最后的顺序在floor的向量中储存，后续这里添加打印功能或者输出功能
*/

void ALAP(vector<vector<int>> map_node, vector<char> map_name, vector<int> end) {

	vector<int> floor;
	for (int i = 0; i < map_node.size(); i++)
		floor.push_back(0);
	for (int i = 0; i < end.size(); i++)
		_DFS(map_node, end[i], floor);

	int line = 1;
	_printline();
	cout << "ALAP结果：" << endl;
	for (int i = 1; i < 200; i++) {

		bool flag = false;
		for (int j = 0; j < floor.size(); j++) {
			if (floor.at(j) == line) {
				floor[j] = 0;
				printf("第%d轮循环中，完成了节点%c\n", i,map_name.at(j));
				break;
			}
			if(j==floor.size()-1)
			flag = true;
		}
		if (flag){
			i--;
			line++;
		}
		
		int tag = 0;
		for (int j = 0; j < floor.size(); j++) {
			if (floor.at(j) != 0)
				break;
			tag++;
		}
		if (tag>=floor.size())
			break;
	}
	printf("循环结束\n");
	_printline();
}

void InfoToCycle(vector<vector<int>> map_node, vector<char> map_name, vector<int> end,int OR,int AND,int NO) {

	vector<int> floor;
	for (int i = 0; i < map_node.size(); i++)
		floor.push_back(0);
	for (int i = 0; i < end.size(); i++)
		_DFS(map_node, end[i], floor);

	vector<int> _temp =_Clear(map_node);
	for (int i = 0; i < _temp.size(); i++)
		printf("%d ", _temp.at(i));
	printf("\n");

	for (int i = 0; i < floor.size(); i++)
		printf("%d ", floor.at(i));
	printf("\n");

}