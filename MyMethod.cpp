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

static vector<vector<int>> Round(vector<vector<int>> list) {
	vector<vector<int>> temp;
	for (int i = list.size() - 1; i >=0; i--) 
		temp.push_back(list.at(i));
	temp.erase(temp.begin());
	vector<int> vec;
	temp.push_back(vec);
	return temp;
}

void AFAP(HashMap map) {

	vector<vector<int>> list;

	map.DelayTime(10,10,10);

	for (int i = 0; i < 200; i++) {
		bool flag = map.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		map.Update();
		map.ClearNode(temp);	
		list.push_back(temp);
		map.Refresh();
	}

	_Print(list, map);
	map.Clear();
}
	//更新可进行使用的门-》三板斧-》进入下一轮循环-》刷新门-》释放已完成节点
void ALAP(HashMap map) {

	map.DelayTime();
	vector<vector<int>> list;
	map.UsableNodeUninitialize();
	int maxTurn;
	cout <<"请输入循环数：";
	cin >> maxTurn;

	for (int i = 0; i < maxTurn; i++) {
		vector<int> temp;
		map.Unupdate();
		map.ClearNode(temp);
		list.push_back(temp);
		map.Refresh();
	}

	bool flag = map.ListCheck();
	if (!flag) {
		cout << "无法完成轮次";
		return;
	}

	vector<vector<int>> temp = Round(list);
	_Print(temp, map);
}

void ToCycle(HashMap map) {

	vector<vector<int>> list;

	map.DelayTime();

	for (int i = 0; i < 200; i++) {
		bool flag = map.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		map.Update();
		map.ClearNode(temp);
		list.push_back(temp);
		map.Refresh();
	}

	_Print(list, map);
	map.Clear();
}

void FromCycle(HashMap map) {
	HashMap Copy_1;
	int turn;
	cout << "请输入进行轮次（例：11）：";
	cin >> turn;

	int temp_1, temp_2, temp_3;
	cout << "请按与、或、非门的顺序输入所需要的时间(例：1 1 1)：";
	cin >> temp_1 >> temp_2 >> temp_3;


	Copy_1 = map;

	vector<vector<int>> list;

	Copy_1.DelayTime(10, 10, 10,temp_1,temp_2,temp_3);

	for (int i = 0; i < 200; i++) {
		bool flag = Copy_1.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		Copy_1.Update();
		Copy_1.ClearNode(temp);
		list.push_back(temp);
		Copy_1.Refresh();
	}
	int min = list.size();
	list.clear();

	if (turn < min) {
		cout << "不可能实现";
		return;
	}



	HashMap Copy_2;
	Copy_2 = map;
	Copy_2.DelayTime(1, 1, 1,temp_1,temp_2,temp_3);

	for (int i = 0; i < 200; i++) {
		bool flag = Copy_2.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		Copy_2.Update();
		Copy_2.ClearNode(temp);
		list.push_back(temp);
		Copy_2.Refresh();
	}
	int max = list.size();
	if (turn > max){
		vector<vector<int>> copy;
		vector<int>vec;
		copy = list;
		list.clear();
		for (int i = 0; i < turn - max; i++)
			list.push_back(vec);
		list.insert(list.end(), copy.begin(), copy.end());
		goto END;
	}
	list.clear();

	for (int x = 0; x < 5; x++) 
		for (int y = 0; y < 5; y++)
			for (int z = 0; z < 5; z++) {
				HashMap Copy = map;
				Copy.DelayTime(x, y, z,temp_1,temp_2,temp_3);

				for (int i = 0; i < 200; i++) {
					bool flag = Copy.ListCheck();
					if (flag)
						break;
					vector<int> temp;
					Copy.Update();
					Copy.ClearNode(temp);
					list.push_back(temp);
					Copy.Refresh();
				}
				int result = list.size();

				if (result == turn)
					goto END;
				list.clear();
			}

	END:_Print(list, map);
}

vector<vector<int>> SPUsing(HashMap map,int &max,int &num1,int &num2,int &num3) {

	vector<vector<int>> vec;
	vector<int> vec_1;
	for (int i = 0; i < map.size; i++)
		vec.push_back(vec_1);
	
	HashMap Copy_1, Copy_2;
	Copy_1 = Copy_2 = map;

	int temp_1, temp_2, temp_3;
	cout << "请按与、或、非门的顺序输入所需要的时间(例：1 1 1)：";
	cin >> temp_1 >> temp_2 >> temp_3;

	num1 = temp_1;
	num2 = temp_2;
	num3 = temp_3;

	Copy_1.DelayTime(10, 10, 10, temp_1, temp_2, temp_3);

	for (int i = 0; i < 200; i++) {
		bool flag = Copy_1.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		Copy_1.Update();
		Copy_1.ClearNode(temp);
		for (int x = 0; x < temp.size(); x++)
			vec.at(temp.at(x)).push_back(i);
		Copy_1.Refresh();
	}

	vector<vector<int>> list;

	Copy_2.DelayTime(1, 1, 1, temp_1, temp_2, temp_3);

	for (int i = 0; i < 200; i++) {
		bool flag = Copy_2.ListCheck();
		if (flag)
			break;
		vector<int> temp;
		Copy_2.Update();
		Copy_2.ClearNode(temp);
		for (int x = 0; x < temp.size(); x++)
			vec.at(temp.at(x)).push_back(i);
		Copy_2.Refresh();
		max = i+1;
	}

	return vec;

}