#include<iostream>
#include <sstream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>

#include "myBlifToV.h"
#include "Hash.h"

using namespace std;

//文件名字
#define NAME "test"

static void _Read(string& model, string& input, string& output, vector<vector<string>>& node, ifstream& src) {

	vector<string> temp;
	string line;
	bool flag = true;

	while (getline(src, line)) {

		char first = line.front();
		if (first == '#')
			continue;

		char second = line.at(1);
		switch (second) {
		case 'm':
			model = line;
			break;
		case 'i':
			input = line;
			break;
		case 'o':
			output = line;
			break;
		case 'n':
			temp.push_back(line);
			while (true) {
				getline(src, line);
				char checkPoint = line.at(1);
				if (checkPoint == 'n') {
					node.push_back(temp);
					temp.clear();
					temp.push_back(line);
				}
				else if (checkPoint == 'e') {
					node.push_back(temp);
					temp.clear();
					break;
				}
				else 
					temp.push_back(line);
			}
			break;
		default:
			cout << "出现预期以外数据，读取可能出现问题" << endl;
			break;
		}
	}

}

static void _ProcessNode(vector<string>& outputNode, vector<string>& inputNode, vector<string>& nodeMap, string input, string output, vector<vector<string>> node) {

	string temp;
	vector<string> node_temp;
	istringstream inp(input);
	istringstream outp(output);

	while (inp >> temp)
		inputNode.push_back(temp);
	if(!inputNode.empty())
		inputNode.erase(inputNode.begin());
	while (outp >> temp)
		outputNode.push_back(temp);
	if (!outputNode.empty())
		outputNode.erase(outputNode.begin());

	nodeMap.insert(nodeMap.end(), inputNode.begin(), inputNode.end());

	for (int i = 0; i < node.size(); i++) {
		string str = node.at(i).at(0);
		istringstream iss(str);
		while (iss >> temp)
			node_temp.push_back(temp);
		nodeMap.push_back(node_temp.back());
	}

}

static void _ProcessEqual(vector<vector<string>>node, vector<vector<string>>& equals) {

	vector<string> temp;
	string str;

	for (int i = 0; i < node.size(); i++) {

		istringstream iss(node.at(i).at(0));
		while (iss >> str)
			temp.push_back(str);
		if (!temp.empty())
			temp.erase(temp.begin());

		string checkLine;
		checkLine = node.at(i).at(1);
		for (int j = 0; j < checkLine.size(); j++)
			if (checkLine.at(j) == '-') {
				temp.push_back("1");
				break;
			}
			else if (checkLine.at(j) == '0') {
				temp.push_back("0");
				break;
			}
			else if (checkLine.at(j) == ' ') {
				temp.push_back("2");
				break;
			}
		equals.push_back(temp);
		temp.clear();
	}

}
//0为非门，1为或门，2为与门

static void _Print(string model, vector<string> _output, vector<string> _input, vector<string> _map, ofstream& outfile, vector<vector<string>> equals) {

	string module = model.substr(7);
	string _node;
	for (int i = 0; i < _output.size(); i++) {
		_node += ", ";
		_node += _output.at(i);
	}
	for (int i = 0; i < _input.size(); i++) {
		_node += ", ";
		_node += _input.at(i);
	}
	string m_temp = "module " + module + "(clk, ret" + _node + ");";
	outfile << m_temp << endl;
	outfile << "input clk, ret;" << endl;


	for (int i = 0; i < _output.size(); i++) {
		string o_temp = "output ";
		o_temp+=_output.at(i);
		o_temp.push_back(';');
		outfile << o_temp << endl;
	}


	for (int i = 0; i < _input.size(); i++) {
		string i_temp = "input ";
		i_temp+=_input.at(i);
		i_temp.push_back(';');
		outfile << i_temp << endl;
	}


	for (int i = 0; i < _map.size(); i++) {
		string w_temp = "wire ";
		w_temp+=_map.at(i);
		w_temp.push_back(';');
		outfile << w_temp << endl;
	}

	for (int i = 0; i < equals.size(); i++) {
		string a_temp = "assign ";
		if (equals.at(i).back() == "0") {
			a_temp += equals.at(i).at(1);
			a_temp.push_back('=');
			a_temp.push_back('~');
			a_temp += equals.at(i).at(0);
			a_temp.push_back(';');
		}
		else if (equals.at(i).back() == "2") {
			a_temp += equals.at(i).at(equals.at(i).size()-2);
			a_temp.push_back('=');
			for (int j = 0; j < equals.at(i).size() - 2; j++) {
				a_temp += equals.at(i).at(j);	
				a_temp.push_back('&');
			}
			a_temp.pop_back();
			a_temp.push_back(';');
		}
		else if (equals.at(i).back() == "1") {
			a_temp += equals.at(i).at(equals.at(i).size() - 2);
			a_temp.push_back('=');
			for (int j = 0; j < equals.at(i).size() - 2; j++) {
				a_temp += equals.at(i).at(j);
				a_temp.push_back('|');
			}
			a_temp.pop_back();
			a_temp.push_back(';');
		}
		outfile << a_temp << endl;
	}

	outfile << "endmodule" << endl;
}

HashMap Transform() {

	string inputName, outputName, s_temp;
	inputName = outputName = NAME;
	cout << "请写入输入文件名字（默认为test）:";
	getline(cin, s_temp);
	if (!s_temp.empty())
		inputName = s_temp;
	inputName += ".blif";
	cout << "请写入输出文件名字（默认为test）:";
	getline(cin, s_temp);
	if (!s_temp.empty())
		outputName = s_temp;
	outputName += ".v";

	ifstream src(inputName);
	ofstream outfile(outputName);
	if (src.is_open())
		cout << "输入文件成功打开" << endl;
	else
		cout << "输入文件打开失败，请查看源文件路径下是否存在" << inputName << "文件" << endl;

	string model, input, output;
	vector<vector<string>> node;
	_Read(model, input, output, node, src);

	vector<string> outputNode, inputNode, nodeMap;
	_ProcessNode(outputNode, inputNode, nodeMap, input, output, node);

	vector<vector<string>> equals;
	_ProcessEqual(node, equals);

	HashMap map;
	map.Initialization(nodeMap, equals, outputNode, inputNode);
	
	if (outfile.is_open()) {
		_Print(model, outputNode, inputNode, nodeMap, outfile, equals);
		cout << "文件打印完成" << endl;
	}
	else
		cout << "verliog文件未成功打开，请检查写入部分" << endl;
	outfile.close();
	src.close();
	return map;
}
