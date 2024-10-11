#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include "myBlifToV.h"
using namespace std;

//输出输入的位置，需要手动修改
#define INPUT_BLIF "C:\\Users\\五月\\Desktop\\程序\\input\\test1.blif"
#define OUTPUT_V "C:\\Users\\五月\\Desktop\\程序\\test100.v"

int BlifToV(vector<vector<int>>& INT, vector<char>& CHAR){

	ifstream src(INPUT_BLIF);
	
	if (src.is_open())
		cout << "目标文件成功打开" << endl;
	else {
		cout << "目标文件打开失败，请查看源文件路径下是否存在test1.blif文件" << endl;
		return 100;
	}
	//读取blif文件
	string line, model, input, output;
	vector<string> temp;
	vector<vector<string>> node;
	while (getline(src, line)) {
		char head = line.front();
		if (head == '.') {
			char second = line.at(1);
			switch (second) {
			case 'm':model = line;
				break;
			case 'i':input = line;
				break;
			case 'o':output = line;
				break;
			case 'n':
				while (true) {
					bool return_flag = false;
					bool exit_flag = false;
					temp.push_back(line);
					while (getline(src, line)) {
						char point = line.at(1);
						if (point == 'n') {
							return_flag = true;
							break;
						}
						else if (point == 'e') {
							exit_flag = true;
							break;
						}
						else
							temp.push_back(line);
					}
					node.push_back(temp);
					temp.clear();
					if (return_flag)
						continue;
					if (exit_flag)
						break;
					cout << "读取循环紊乱，修复读取逻辑" << endl;
				}
				break;
			case 'e':cout << "出现e开头的队列，请检查读取是否存在问题" << endl;
				break;
			default:cout << "出现预期以外数据，读取可能出现问题" << endl;
				break;
			}
		}
	}

	ofstream outfile(OUTPUT_V);
	//处理读取的数据
	vector<char> p_output, p_input, map;
	for (int i = 8; i < input.size(); i += 2) {
		p_input.push_back(input.at(i));
		map.push_back(input.at(i));
	}
	for (int i = 9; i < output.size(); i += 2) {
		p_output.push_back(output.at(i));
		map.push_back(output.at(i));
	}
	for (int i = 0; i < node.size(); i++)
		for (int j = 7; j < node[i][0].size(); j += 2) {
			bool flag = false;
			for (int k = 0; k < map.size(); k++) {
				if (map[k] == node[i][0].at(j))
					flag = true;
			}
			if (!flag)
				map.push_back(node[i][0].at(j));
		}

	vector<vector<char>> equals;
	vector<char> info;
	for (int i = 0; i < node.size(); i++) {
		bool only_flag = false;
		if (node[i].size() > 2)
			only_flag = true;
		vector<char> point;
		for (int j = 7; j < node[i][0].size(); j += 2)
			point.push_back(node[i][0].at(j));
		for (int j = 1; j < node[i].size(); j++) {
			if (j > 1)
				info.push_back('|');
			int num = 0, temp = 0;
			for (int k = 0; k < point.size() - 1; k++)
				if (node[i][j].at(k) != '-')
					num++;
			if (num > 1 && node[i].size() > 2)
				info.push_back('(');
			for (int k = 0; k < point.size() - 1; k++) {
				if (node[i][j].at(k) == '1') {
					if (temp > 0)
						info.push_back('&');
					info.push_back(point[k]);
					temp++;
				}
				if (node[i][j].at(k) == '0') {
					if (temp > 0)
						info.push_back('&');
					info.push_back('~');
					info.push_back(point[k]);
					temp++;
				}
			}
			if (num > 1 && node[i].size() > 2)
				info.push_back(')');
		}
		info.push_back(point[point.size() - 1]);
		equals.push_back(info);
		info.clear();
	}
	//给其他程序提供数据
	for (int i = 0; i < map.size(); i++)
		cout << map[i] << endl;
	//打印
	if (outfile.is_open()) {
		string module = model.substr(7);
		string r_node;
		for (int i = 0; i < p_output.size(); i++) {
			r_node += ", ";
			r_node.push_back(p_output[i]);
		}
		for (int i = 0; i < p_input.size(); i++) {
			r_node += ", ";
			r_node.push_back(p_input[i]);
		}
		string m_temp = "module " + module + "(clk, ret" + r_node + ");";
		outfile << m_temp << endl;
		outfile << "input clk, ret;" << endl;
		for (int i = 0; i < p_output.size(); i++) {
			string o_temp = "output ";
			o_temp.push_back(p_output[i]);
			o_temp.push_back(';');
			outfile << o_temp << endl;
		}
		for (int i = 0; i < p_input.size(); i++) {
			string i_temp = "input ";
			i_temp.push_back(p_input[i]);
			i_temp.push_back(';');
			outfile << i_temp << endl;
		}
		for (int i = 0; i < map.size(); i++) {
			string w_temp = "wire ";
			w_temp.push_back(map[i]);
			w_temp.push_back(';');
			outfile << w_temp << endl;
		}
		for (int i = 0; i < equals.size(); i++) {
			string a_temp = "assign ";
			a_temp.push_back(equals[i][equals[i].size() - 1]);
			a_temp += " = ";
			for (int j = 0; j < equals[i].size() - 1; j++)
				a_temp.push_back(equals[i][j]);
			a_temp.push_back(';');
			outfile << a_temp << endl;
		}
		outfile << "endmodule" << endl;
		cout << "文件打印完成" << endl;
	}
	else
		cout << "verliog文件未成功打开，请检查写入部分" << endl;

	outfile.close();
	src.close();
	return 1;
}
