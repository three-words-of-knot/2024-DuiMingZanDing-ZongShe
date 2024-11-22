#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>

#include "MyMethod.h"
#include "Hash.h"
#include "Info.h"

using namespace std;

static void _Print(vector<vector<int>> _list,HashMap _map) {

	string i_temp = "Input :";
	for (int i = 0; i < _map.startNode.size(); i++) {
		i_temp+=_map.startNode.at(i);
		i_temp.push_back(',');
	}
	i_temp.pop_back();
	cout<<i_temp<<" ";

	string o_temp = "Output :";
	for (int i = 0; i < _map.endNode.size(); i++){
		o_temp+=_map.endNode.at(i);
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
		vector<string> line_1, line_2, line_3;
		for (int j = 0; j < _list.at(i).size(); j++) {
			int target = _list.at(i).at(j);
			if (_map.nodeType.at(target) == 1)
				line_1.push_back(_map.nodeName.at(target));
			else if(_map.nodeType.at(target) == 2)
				line_2.push_back(_map.nodeName.at(target));
			else
				line_3.push_back(_map.nodeName.at(target));
		}


		string temp_2 = "{";
		for (int j = 0; j < line_2.size(); j++) {
			temp_2 += line_2.at(j);
			temp_2.push_back(' ');
		}
		if (temp_2.size() > 1)
			temp_2.pop_back();
		temp_2.push_back('}');
		n_temp += temp_2;
		n_temp.push_back(',');

		string temp_3 = "{";
		for (int j = 0; j < line_3.size(); j++) {
			temp_3 += line_3.at(j);
			temp_3.push_back(' ');
		}
		if (temp_3.size() > 1)
			temp_3.pop_back();
		temp_3.push_back('}');
		n_temp += temp_3;
		n_temp.push_back(',');

		string temp_1 = "{";
		for (int j = 0; j < line_1.size(); j++) {
			temp_1 += line_1.at(j);
			temp_1.push_back(' ');
		}
		if(temp_1.size()>1)
			temp_1.pop_back();
		temp_1.push_back('}');
		n_temp += temp_1;


		cout <<n_temp <<endl;
	}
}

static void _Print(vector<vector<int>> _list, HashMap _map,vector<int> max) {

	string i_temp = "Input :";
	for (int i = 0; i < _map.startNode.size(); i++) {
		i_temp += _map.startNode.at(i);
		i_temp.push_back(',');
	}
	i_temp.pop_back();
	cout << i_temp << " ";

	string o_temp = "Output :";
	for (int i = 0; i < _map.endNode.size(); i++) {
		o_temp += _map.endNode.at(i);
		o_temp.push_back(',');
	}
	o_temp.pop_back();
	cout << o_temp << endl;

	string t_temp = "Total ";
	t_temp += to_string(_list.size());
	t_temp += " Cycles";
	cout << t_temp << ",与门" << max.at(0) << "个，或门" << max.at(1) << "个，非门" << max.at(2) << "个" << endl;;

	for (int i = 0; i < _list.size(); i++) {

		string n_temp = "Cycle ";
		n_temp += to_string(i + 1);
		n_temp += ':';
		vector<string> line_1, line_2, line_3;
		for (int j = 0; j < _list.at(i).size(); j++) {
			int target = _list.at(i).at(j);
			if (_map.nodeType.at(target) == 1)
				line_1.push_back(_map.nodeName.at(target));
			else if (_map.nodeType.at(target) == 2)
				line_2.push_back(_map.nodeName.at(target));
			else
				line_3.push_back(_map.nodeName.at(target));
		}


		string temp_2 = "{";
		for (int j = 0; j < line_2.size(); j++) {
			temp_2 += line_2.at(j);
			temp_2.push_back(' ');
		}
		if (temp_2.size() > 1)
			temp_2.pop_back();
		temp_2.push_back('}');
		n_temp += temp_2;
		n_temp.push_back(',');

		string temp_3 = "{";
		for (int j = 0; j < line_3.size(); j++) {
			temp_3 += line_3.at(j);
			temp_3.push_back(' ');
		}
		if (temp_3.size() > 1)
			temp_3.pop_back();
		temp_3.push_back('}');
		n_temp += temp_3;
		n_temp.push_back(',');

		string temp_1 = "{";
		for (int j = 0; j < line_1.size(); j++) {
			temp_1 += line_1.at(j);
			temp_1.push_back(' ');
		}
		if (temp_1.size() > 1)
			temp_1.pop_back();
		temp_1.push_back('}');
		n_temp += temp_1;


		cout << n_temp << endl;
	}
}

static vector<vector<int>> _Calc(HashMap map,int AND,int NO,int OR) {

	Info Cost;
	vector<vector<int>> result;
	vector<int> temp, mapper;
	Cost.Initialization(3, 2, 1, OR, AND, NO);

	for (int i = 0; i < map.size; i++)
		mapper.push_back(0);
	for (int i = 0; i < map.startNode.size(); i++) {
		int id = map.FindIdByName(map.startNode.at(i));
		if (id >= 0)
			mapper.at(id) = 1;
	}

	for (int i = 0; i < 200; i++) {
		//1代表已完成，2代表可以进行，3代表正在运算
		for (int j = 0; j < map.size; j++) {
			bool flag = true;
			if (!map.nodeMap.at(j).empty()) 
				for (int k = 0; k < map.nodeMap.at(j).size(); k++) {
					int id = map.nodeMap.at(j).at(k);
					if (mapper.at(id) !=1)
						flag = false;
				}

			if (flag&&mapper.at(j)==0)
				mapper.at(j) = 2;
		}
		//高亮节点
		for (int o = 0; o < mapper.size(); o++) {
			cout << mapper.at(o);
		}
		cout << endl;
		bool _check = true;
		for (int j = 0; j < map.size; j++)
			if (mapper.at(j) != 1)
				_check = false;
		if (_check)
			break;
		//检查是否还有未完成节点

		for (int j = 0; j < map.size; j++) {
			int result = Cost.CheckDoor(0);
			if (result == -1)
				break;
			if (map.nodeType.at(j) == 2 && mapper.at(j) == 2) {
				mapper.at(j) = 3;
				temp.push_back(j);
				Cost.UseDoor(0, result,j);
			}
		}

		for (int j = 0; j < map.size; j++) {
			int result = Cost.CheckDoor(1);
			if (result == -1)
				break;
			if (map.nodeType.at(j) == 3 && mapper.at(j) == 2) {
				mapper.at(j) = 3;
				temp.push_back(j);
				Cost.UseDoor(1, result,j);
			}
		}

		for (int j = 0; j < map.size; j++) {
			int result = Cost.CheckDoor(2);
			if (result == -1)
				break;
			if (map.nodeType.at(j) == 1 && mapper.at(j) == 2) {
				mapper.at(j) = 3;
				temp.push_back(j);
				Cost.UseDoor(2, result,j);
			}
		}

		Cost.Clear(mapper);
		result.push_back(temp);
		temp.clear();

	}

	return result;
}

static void _ZeroCalc(HashMap map,vector<int> max,int turn, vector<vector<int>> &answers, vector<vector<vector<int>>> &lists) {

	int A = max.at(0), O = max.at(1), N = max.at(2);
	if (A != 0)
		A = 1;
	if (O != 0)
		O = 1;
	if (N != 0)
		N = 1;
	vector<int> Vec;
	Vec.push_back(A);
	Vec.push_back(O);
	Vec.push_back(N);

	for (; A <= max.at(0); A++) {
		for (; O <= max.at(1); O++) {
			for (; N <= max.at(2); N++) {
				vector<vector<int>> list = _Calc(map, A, O, N);
				if (list.size() == turn) {
					vector<int> vec;
					vec.push_back(A);
					vec.push_back(O);
					vec.push_back(N);
					answers.push_back(vec);
					lists.push_back(list);
				}
			}
			N = Vec.at(2);
		}
		N = Vec.at(2);
		O = Vec.at(1);
	}

}

static vector<int> _CheckFloor(HashMap map) {

	int A=0, N=0, O=0;
	for (int i = 1; i <= map.maxFloor; i++) {

		int a_temp = 0, n_temp = 0, o_temp = 0;
		for(int j=0;j<map.size;j++)
			if(map.nodeFloor.at(j) == i)
				switch (map.nodeType.at(j)) {
				case 1:
					n_temp++;
					break;
				case 2:
					a_temp++;
					break;
				case 3:
					o_temp++;
					break;
				default:
					break;
			}

		if (A < a_temp)
			A = a_temp;
		if (N < n_temp)
			N = n_temp;
		if (O < o_temp)
			O = o_temp;

	}

	vector<int> vec;
	vec.push_back(A);
	vec.push_back(O);
	vec.push_back(N);
	return vec;
}

static int _Compare(vector<vector<int>> answers) {


	vector<int> vec = answers.at(0);	
	int min = 0, result = 0;
	for (int i = 0; i < 3; i++)
		min += answers.at(0).at(i);
	if (answers.size() == 1)
		return 0;

	for (int i = 1; i < answers.size(); i++) {
		int sum = 0;
		for (int j = 0; j < 3; j++)
			sum += answers.at(i).at(j);
		if (sum < min) {
			min = sum;
			result = i;
		}
	}

	return result;
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

void ALAP(HashMap map) {

	vector<vector<int>>	list;
	vector<int> vec;
	vector<int> mapper;
	int turn;
	int count = 0;
	int size = map.size-map.startNode.size();

	cout << "请输入最大轮次（例：11）：";
	cin >> turn;
	if (turn < map.maxFloor||turn>size) {
		cout << "这个数据不能实现" << endl;
		return;
	}
	for (int i = 0; i < map.size; i++)
		mapper.push_back(0);

	for (int i = 1; i <= map.maxFloor; i++) {
		bool flag = false;
		for (int j = 0; j < map.size; j++) {

			if (map.nodeFloor.at(j) == i) {
				mapper.at(j) = 1;
				count++;
				vec.push_back(j);
			}

			if (i + size - count == turn)
				flag = true;
			if (flag)
				break;
		}
		list.push_back(vec);
		vec.clear();
		if (flag)
			break;
	}

	for (int i = 1; i <= map.maxFloor; i++)
		for(int j=0;j<map.size;j++)
			if (map.nodeFloor.at(j) == i && mapper.at(j) == 0) {
				mapper.at(j) = 1;
				vec.push_back(j);	
				list.push_back(vec);
				vec.clear();
			}

	_Print(list, map);
}

void ToCycle(HashMap map) {

	int AND, OR, NO;
	cout << "请按顺序输入与，或，非门的数量（例：7 8 9）：";
	cin >> AND >> OR >> NO;

	vector<vector<int>> list =_Calc(map, AND, NO, OR);
	_Print(list, map);
}

void FromCycle(HashMap map) {

	vector<int> max = _CheckFloor(map);//与或非
	vector<vector<vector<int>>> lists;
	vector<vector<int>> answers;
	int turn;
	cout << "请输入进行轮次（例：11）：";
	cin >> turn;

	for(int i=1;i<=max.at(0);i++)
		for(int j=1;j<=max.at(1);j++)
			for (int k = 1; k <= max.at(2); k++) {
				vector<vector<int>> list = _Calc(map, i, k, j);
				if (list.size() == turn) {	
					vector<int> vec;
					vec.push_back(i);
					vec.push_back(j);
					vec.push_back(k);
					answers.push_back(vec);
					lists.push_back(list);
				}
			}


	for (int i = 0; i < 3; i++) 
		if (max.at(i) == 0) {
			_ZeroCalc(map,max,turn,answers,lists);

			break;
		}


	if (answers.empty())
		cout << "这个数据不能实现" << endl;
	else {	
		int id = _Compare(answers);
		_Print(lists.at(id), map, answers.at(id));
	}
}
//

