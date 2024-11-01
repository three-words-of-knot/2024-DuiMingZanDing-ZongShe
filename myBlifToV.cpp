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
#define INPUT_NAME "\\input\\test1.blif"
#define OUTPUT_NAME "\\test1.v"

static string _GetDirectory(const std::string& filePath) {

	size_t lastSlash = filePath.find_last_of("/\\");

	if (lastSlash == std::string::npos) {
		return "";
	}

	return filePath.substr(0, lastSlash);

}

static void _Read(string& model, string& input, string& output, vector<vector<string>>& node, ifstream& src) {

	vector<string> _temp;
	string _line;
	bool _flag = true;

	while (getline(src, _line)) {
		char first = _line.front();
		if (first == '#')
			continue;

		char second = _line.at(1);
		switch (second) {
		case 'm':
			model = _line;
			break;
		case 'i':
			input = _line;
			break;
		case 'o':
			output = _line;
			break;
		case 'n':
			while (_flag) {
				_temp.push_back(_line);
				while (getline(src, _line)) {
					char point = _line.at(1);
					if (point == 'n')
						break;
					else if (point == 'e') {
						_flag = false;
						break;
					}
					else
						_temp.push_back(_line);
				}
				node.push_back(_temp);
				_temp.clear();
			}
			break;
		default:
			cout << "出现预期以外数据，读取可能出现问题" << endl;
			break;
		}
	}

}

static void _ProcessNode(vector<string>& _output, vector<string>& _input, vector<string>& _map, string input, string output, vector<vector<string>> node) {

	string temp;
	vector<string> node_temp;
	istringstream inp(input);
	istringstream outp(output);

	while (inp >> temp)
		_input.push_back(temp);
	if(!_input.empty())
		_input.erase(_input.begin());
	while (outp >> temp)
		_output.push_back(temp);
	if (!_output.empty())
		_output.erase(_output.begin());

	_map.insert(_map.end(), _input.begin(), _input.end());

	for (int i = 0; i < node.size(); i++) {
		string str = node.at(i).at(0);
		istringstream iss(str);
		while (iss >> temp)
			node_temp.push_back(temp);
		_map.push_back(node_temp.back());
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

		if (node.at(i).size() >= 3)
			temp.push_back("3");
		else if (node.at(i).at(1).at(0) == '0')
			temp.push_back("1");
		else
			temp.push_back("2");

		equals.push_back(temp);
		temp.clear();
	}

}

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
		if (equals.at(i).back() == "1") {
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
		else if (equals.at(i).back() == "3") {
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
	string INPUT, OUTPUT;
	INPUT = OUTPUT = _GetDirectory(__FILE__);
	INPUT += INPUT_NAME;
	OUTPUT += OUTPUT_NAME;

	ifstream src(INPUT);
	ofstream outfile(OUTPUT);
	if (src.is_open())
		cout << "目标文件成功打开" << endl;
	else
		cout << "目标文件打开失败，请查看源文件路径下是否存在test1.blif文件" << endl;

	string line, model, input, output;

	vector<string> temp;

	vector<vector<string>> node;

	_Read(model, input, output, node, src);

	vector<string> _output, _input, _map;

	_ProcessNode(_output, _input, _map, input, output, node);

	vector<vector<string>> equals;

	_ProcessEqual(node, equals);
	
	HashMap map;

	map.Initialization(_map, equals, _output, _input);

	if (outfile.is_open()) {
		_Print(model, _output, _input, _map, outfile, equals);
		cout << "文件打印完成" << endl;
	}
	else
		cout << "verliog文件未成功打开，请检查写入部分" << endl;
	outfile.close();
	src.close();
	return map;
}
