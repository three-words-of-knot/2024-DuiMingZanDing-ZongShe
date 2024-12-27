#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>

#include"MyMethod.h"
#include"Hash.h"

using namespace std;
#define NAME "test"

static void _Print(vector<vector<int>> vec,HashMap map,ofstream &outfile,int A,int B,int C,int D) {

	outfile << "Min" << endl;
	string A_string;
	for (int i = 1; i <=A+1; i++) {
		if(i!=1)
			A_string += to_string(i);
		A_string += "XA";
		A_string += to_string(i);
		if(i!=A+1)
			A_string += "+";
	}
	outfile << A_string << endl;
	outfile << "Subject To" << endl;

	for(int i=0;i<vec.size();i++)
		if (!vec.at(i).empty()) {
			string temp;
			int start, end;
			start = vec.at(i).at(0) + 1;
			end = vec.at(i).at(1) + 1;
			for (int j = start; j <= end; j++) {
				temp += "X";
				temp += map.nodeName.at(i);
				temp += to_string(j);
				if (j != end)
					temp += "+";
			}
			temp += "=1";
			outfile << temp<<endl;
		}

	for (int i = 0; i < map.size; i++) 
		if (!map.nodeMap.at(i).empty()) {
			string temp;
			int start, end;
			start = vec.at(i).at(0) + 1;
			end = vec.at(i).at(1) + 1;
			for (int j = start; j <= end; j++) {
				if (j != 1)
					temp += to_string(j);
				temp += "X";
				temp += map.nodeName.at(i);
				temp += to_string(j);
				if (j != end)
					temp += "+";
			}

			bool flag = true;

			for (int j = 0; j < map.nodeMap.at(i).size(); j++) {
				int id = map.nodeMap.at(i).at(j);
				if (vec.at(id).empty())
					continue;
				start = vec.at(id).at(0) + 1;
				end = vec.at(id).at(1) + 1;
				for (int k = start; k <= end; k++) {
					temp += "-";
					if (k != 1)
						temp += to_string(k);
					temp += "X";
					temp += map.nodeName.at(id);
					temp += to_string(k);
				}
				flag = false;
			}

			if (flag)
				continue;
			temp += ">=1";
			outfile << temp << endl;

		}

	for (int i = 0; i < map.endNode.size(); i++) {
		string temp;
		temp += to_string(A + 1);
		temp += "XA";
		temp += to_string(A + 1);
		int id = map.FindIdByName(map.endNode.at(i));
		int start, end;
		start = vec.at(id).at(0) + 1;
		end = vec.at(id).at(1) + 1;
		for (int j = start; j <= end; j++) {
			temp += "-";
			if (j != 1)
				temp += to_string(j);
			temp += "X";
			temp += map.nodeName.at(id);
			temp += to_string(j);
		}
		temp += ">=1";
		outfile << temp << endl;
	}

	string ak_1, ak_2, ak_3;
	ak_1 += "ak1=";//与或非
	ak_2 += "ak2=";
	ak_3 += "ak3=";
	ak_1 += to_string(B);
	ak_2 += to_string(C);
	ak_3 += to_string(D);
	outfile << ak_1 << endl << ak_2 << endl << ak_3 << endl;

	for (int j = 1; j <= A; j++) {
		for (int k = 0; k < 3; k++) {
			string temp;
			for(int i=0;i<map.size;i++)
				if (map.nodeType.at(i) == k) 
					if(!vec.at(i).empty())
						if (vec.at(i).at(0) + 1 <= j && vec.at(i).at(1) + 1 >= j) {
							temp += "X";
							temp += map.nodeName.at(i);
							temp += to_string(j);
							temp += "+";
						}	
			if (temp.empty())
				continue;
			temp.pop_back();
			switch (k) {
			case 0:
				temp += "-ak3<=0";
				break;
			case 1:
				temp += "-ak2<=0";
				break;
			case 2:
				temp += "-ak1<=0";
				break;
			default:
				break;
			}
			outfile << temp << endl;
		}
	}

	//差一点

}

void Transformer(HashMap map) {

	int num1, num2, num3;
	num1 = num2 = num3 = 0;
	int temp = 0;
	vector<vector<int>> vec;
	vec = SPUsing(map,temp,num1,num2,num3);

	string name,outputName;
	outputName = NAME;
	cout << "请写入输出文件名字（默认为test）:";
	getline(cin, name);
	if (!name.empty())
		outputName = name;
	outputName += ".lp";
	ofstream outfile(outputName);

	if (outfile.is_open()) {
		_Print(vec,map,outfile,temp,num1,num2,num3);
		cout << "文件打印完成" << endl;
	}
	else
		cout << "lp文件未成功打开，请检查写入部分" << endl;
	outfile.close();
//
}