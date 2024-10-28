#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>

#include "MyMethod.h"
#include "Hash.h"

using namespace std;

static void _Print(vector<vector<int>> _list,HashMap _map) {

	string i_temp = "Input :";
	for (int i = 0; i < _map.startNode.size(); i++) {
		i_temp.push_back(_map.startNode.at(i));
		i_temp.push_back(',');
	}
	i_temp.pop_back();
	cout<<i_temp<<endl;

	string o_temp = "Output :";
	for (int i = 0; i < _map.endNode.size(); i++){
		o_temp.push_back(_map.endNode.at(i));
		o_temp.push_back(',');
	}
	o_temp.pop_back();
	cout << o_temp << endl;

	string t_temp = "Total ";
	t_temp += to_string(_list.size());
	t_temp += " Cycles";
	cout << t_temp << endl;

	for (int i = 0; i < _list.size(); i++){
		string n_temp = "Cycle ";
		n_temp += to_string(i + 1);
		n_temp += ':';
		vector<char> line_1, line_2, line_3;
		for (int j = 0; j < _list.at(i).size(); j++) {
			int target = _list.at(i).at(j);
			if (_map.nodeType.at(target) == 1)
				line_1.push_back(_map.nodeName.at(target));
			else if(_map.nodeType.at(target) == 2)
				line_2.push_back(_map.nodeName.at(target));
			else
				line_3.push_back(_map.nodeName.at(target));
		}

			string temp_3 = "{";
		for (int j = 0; j < line_3.size(); j++) {
			temp_3.push_back(line_3.at(j));
			temp_3.push_back(' ');
		}
		if (temp_3.size() > 1)
			temp_3.pop_back();
		temp_3.push_back('}');
		n_temp += temp_3;
		n_temp.push_back(',');

		string temp_2 = "{";
		for (int j = 0; j < line_2.size(); j++) {
			temp_2.push_back(line_2.at(j));
			temp_2.push_back(' ');
		}
		if (temp_2.size() > 1)
			temp_2.pop_back();
		temp_2.push_back('}');
		n_temp += temp_2;
		n_temp.push_back(',');

		string temp_1 = "{";
		for (int j = 0; j < line_1.size(); j++) {
			temp_1.push_back(line_1.at(j));
			temp_1.push_back(' ');
		}
		if(temp_1.size()>1)
			temp_1.pop_back();
		temp_1.push_back('}');
		n_temp += temp_1;


		cout <<n_temp <<endl;
	}
}

static void TC_Read(int& AND,int &NO,int &OR) {
	cout << "请按顺序输入与，或，非门的数量（例：7 8 9）：";
	cin >> AND >> OR >> NO;
}

static void _Calc(HashMap _map,int _and,int _no,int _or,vector<vector<int>> &list) {
	
	vector<int>temp;

	vector<int> mapper;
	for (int i = 0; i < _map.size; i++)
		mapper.push_back(0);
	for (int i = 0; i < _map.startNode.size(); i++) {
		int temp = _map.FindName(_map.startNode.at(i));
		if (temp >= 0)
			mapper.at(temp) = 1;
	}

	int AND = _and;
	int NO = _no;
	int OR = _or;


	for (int i = 0; i < 200; i++) {

		int flag = true;

		for (int j = 0; j < mapper.size(); j++)
			if (mapper.at(j) != 1)
				flag = false;

		if (flag)
			break;

		for (int k = 0; k < _map.size; k++) {
			bool flag_1 = false;
			for (int j = 0; j < _map.size; j++) {
				if (_map.FindInNodeMap(j, k) > 0 && mapper.at(j) != 1) {
					flag_1 = true;
				}
			}
			if (flag_1) {
				continue;
			}

			else if (mapper.at(k) == 0)
				mapper.at(k) = 2;
		}

		for (int j = 0; j < _map.size; j++) {
			if (AND <= 0)
				break;
			if (_map.nodeType.at(j) == 3 && mapper.at(j) == 2) {
				mapper.at(j) = 1;
				AND--;
				temp.push_back(j);
			}
		}

		for (int j = 0; j < _map.size; j++) {
			if (OR <= 0)
				break;
			if (_map.nodeType.at(j) == 2 && mapper.at(j) == 2) {
				mapper.at(j) = 1;
				OR--;
				temp.push_back(j);
			}
		}

		for (int j = 0; j < _map.size; j++) {
			if (NO <= 0)
				break;
			if (_map.nodeType.at(j) == 1 && mapper.at(j) == 2) {
				mapper.at(j) = 1;
				NO--;
				temp.push_back(j);
			}
		}

		list.push_back(temp);
		temp.clear();
		AND = _and;
		NO = _no;
		OR = _or;

	}

}

static void _CheckFloor(HashMap _map,vector<int>&max) {

	for (int i = 1; i <= _map.maxFloor; i++) {

		int _and = 0, _or = 0, _no = 0;

		for(int j = 0; j < _map.size;j++)
			if(_map.nodeFloor.at(j)==i)
				switch (_map.nodeType.at(j)) {
				case 1:
					_no++;
					break;
				case 2:
					_or++;
					break;
				case 3:
					_and++;
					break;
				default:
					break;
				}

		if (_no > max.at(0))
			max.at(0) = _no;
		if (_or > max.at(1))
			max.at(1) = _or;
		if (_and > max.at(2))
			max.at(2) = _and;

	}

}

void AFAP(HashMap _map) {
	vector<vector<int>> list;
	for (int i = 1; i < 200; i++) {
		vector<int> temp;
		for (int j = 0; j < _map.size; j++)
			if (_map.nodeFloor.at(j) == i)
				temp.push_back(j);
		if (temp.empty())
			break;
		list.push_back(temp);
	}

	_Print(list, _map);
}

void ALAP(HashMap _map) {

	vector<vector<int>> list;
	vector<int> mapper;
	for (int i = 0; i < _map.size; i++)
		mapper.push_back(0);
	int _floornum = 1;
	for (int i = 0; i <200; i++) {
		vector<int> temp;
		for(int j=0;j<_map.size;j++)
			if (_map.nodeFloor.at(j) == _floornum&&mapper.at(j)==0) {
				mapper.at(j) = 1;
				temp.push_back(j);
				break;
			}
		if (temp.empty()) {
			_floornum++;
			continue;
		}
		list.push_back(temp);
	}

	_Print(list, _map);

}

void ToCycle(HashMap _map) {

	vector<vector<int>> list;
	int _and, _no, _or;
	TC_Read(_and, _no, _or);
	
	_Calc(_map, _and, _no, _or, list);

	_Print(list, _map);
}

void FromCycle(HashMap _map) {

	vector<vector<vector<int>>> _check;
	vector < vector<int>>mapper;
	vector<int> answer;
	vector<vector<int>> list;
	int turn;
	cout << "请按顺序输入循环次数（例：11）：";
	cin >> turn;

	vector<int>max;//非 或 与
	for (int i = 0; i < 3; i++)
		max.push_back(0);

	_CheckFloor(_map, max);

	for(int i=1;i<=max.at(2);i++)
		for(int j=1;j<=max.at(1);j++)
			for (int k = 1; k <= max.at(0); k++){
				_Calc(_map, i, k, j, list);
				if (list.size() == turn) {
					_check.push_back(list);
					answer.push_back(i);
					answer.push_back(j);
					answer.push_back(k);
					mapper.push_back(answer);
					answer.clear();
				}
				list.clear();
			}

	if (_check.empty())
		cout << "这个数据不能实现" << endl;
	else {
		cout << "与门数最少为：" << mapper.front().at(0) << endl;
		cout << "或门数最少为：" << mapper.front().at(1) << endl;
		cout << "非门数最少为：" << mapper.front().at(2) << endl;
	}

}