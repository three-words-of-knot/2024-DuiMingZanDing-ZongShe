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
		i_temp+=_map.startNode.at(i);
		i_temp.push_back(',');
	}
	i_temp.pop_back();
	cout<<i_temp<<endl;

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

static vector<vector<int>> _Calc(HashMap map,int AND,int NO,int OR) {

	vector<vector<int>> result;
	vector<int> temp, mapper;
	int A=AND, N=NO, O=OR;

	for (int i = 0; i < map.size; i++)
		mapper.push_back(0);
	for (int i = 0; i < map.startNode.size(); i++) {
		int id = map.FindIdByName(map.startNode.at(i));
		if (id >= 0)
			mapper.at(id) = 1;
	}

	for (int i = 0; i < 200; i++) {

		for (int j = 0; j < map.size; j++) {
			bool flag = true;
			if (!map.nodeMap.at(j).empty()) 
				for (int k = 0; k < map.nodeMap.at(j).size(); k++) {
					int id = map.nodeMap.at(j).at(k);
					if (mapper.at(id) != 1)
						flag = false;
				}

			if (flag&&mapper.at(j)==0)
				mapper.at(j) = 2;
		}
		//高亮节点

		bool _check = true;
		for (int j = 0; j < map.size; j++)
			if (mapper.at(j) != 1)
				_check = false;
		if (_check)
			break;
		//检查是否还有未完成节点

		for (int j = 0; j < map.size; j++) {
			if (A <= 0)
				break;
			if (map.nodeType.at(j) == 2 && mapper.at(j) == 2) {
				A--;
				mapper.at(j) = 1;
				temp.push_back(j);
			}
		}

		for (int j = 0; j < map.size; j++) {
			if (N <= 0)
				break;
			if (map.nodeType.at(j) == 1 && mapper.at(j) == 2) {
				N--;
				mapper.at(j) = 1;
				temp.push_back(j);
			}
		}

		for (int j = 0; j < map.size; j++) {
			if (O <= 0)
				break;
			if (map.nodeType.at(j) == 3 && mapper.at(j) == 2) {
				O--;
				mapper.at(j) = 1;
				temp.push_back(j);
			}
		}


		result.push_back(temp);
		temp.clear();
		A = AND;
		N = NO;
		O = OR;

	}

	return result;
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

static vector<int> _Compare(vector<vector<int>> answers) {


	vector<int> vec = answers.at(0);	
	int min = 0, result = 0;
	for (int i = 0; i < 3; i++)
		min += answers.at(0).at(i);
	if (answers.size() == 1)
		return vec;

	for (int i = 1; i < answers.size(); i++) {
		int sum = 0;
		for (int j = 0; j < 3; j++)
			sum += answers.at(i).at(j);
		if (sum < min) {
			min = sum;
			result = i;
		}
	}

	return answers.at(result);
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
	for (int i = 0; i < 200; i++) {
		vector<int> temp;
		for (int j = 0; j < _map.size; j++)
			if (_map.nodeFloor.at(j) == _floornum && mapper.at(j) == 0) {
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

void ToCycle(HashMap map) {

	int AND, OR, NO;
	cout << "请按顺序输入与，或，非门的数量（例：7 8 9）：";
	cin >> AND >> OR >> NO;

	vector<vector<int>> list =_Calc(map, AND, NO, OR);
	_Print(list, map);
}

void FromCycle(HashMap map) {

	vector<int> max = _CheckFloor(map);//与或非
	vector<int> vec;
	vector<vector<int>> answers;
	int turn;
	cout << "请按顺序输入循环次数（例：11）：";
	cin >> turn;

	for(int i=1;i<=max.at(0);i++)
		for(int j=1;j<=max.at(1);j++)
			for (int k = 1; k <= max.at(2); k++) {
				vector<vector<int>> list = _Calc(map, i, k, j);
				if (list.size() == turn) {
					vec.push_back(i);
					vec.push_back(j);
					vec.push_back(k);
					answers.push_back(vec);
					vec.clear();
				}
				list.clear();
			}

	if (answers.empty())
		cout << "这个数据不能实现" << endl;
	else {	
		vector<int> answer = _Compare(answers);
		cout << "与门数最少为：" << answer.at(0) << endl;
		cout << "或门数最少为：" << answer.at(1) << endl;
		cout << "非门数最少为：" << answer.at(2) << endl;
	}
}
