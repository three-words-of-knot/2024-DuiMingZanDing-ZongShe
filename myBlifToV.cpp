#include<iostream>
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

static int _FindInVector(vector<char> _vector, char _target) {

	for (int i = 0; i < _vector.size(); i++)
		if (_vector.at(i) == _target)
			return i;
	return -1;

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

/*这两处实用性极差，请后续修改*/
static void _ProcessNode(vector<char>& _output, vector<char>& _input, vector<char>& _map, string input, string output, vector<vector<string>> node) {

	for (int i = 8; i < input.size(); i += 2) {
		_input.push_back(input.at(i));
		_map.push_back(input.at(i));
	}
	for (int i = 9; i < output.size(); i += 2) {
		_output.push_back(output.at(i));
		_map.push_back(output.at(i));
	}
	for (int i = 0; i < node.size(); i++)
		for (int j = 7; j < node.at(i).at(0).size(); j += 2)
			if (_FindInVector(_map, node.at(i).at(0).at(j)) < 0)
				_map.push_back(node.at(i).at(0).at(j));

}

static void _ProcessEqual(vector<vector<string>>node, vector<vector<char>>& equals) {

	vector<char>_temp;
	for (int i = 0; i < node.size(); i++) {
		vector<char> line;
		for (int j = 7; j < node.at(i).at(0).size(); j += 2)
			line.push_back(node.at(i).at(0).at(j));
		if (node.at(i).size() >= 3) {
			_temp.push_back(line.back());
			_temp.push_back('=');
			for (int j = 0; j < line.size() - 1; j++) {
				_temp.push_back(line.at(j));
				_temp.push_back('|');
			}
			_temp.pop_back();
		}
		else if (node.at(i).at(1).at(0) == '0') {
			_temp.push_back(line.back());
			_temp.push_back('=');
			_temp.push_back('~');
			_temp.push_back(line.front());

		}
		else {

			_temp.push_back(line.back());
			_temp.push_back('=');
			for (int j = 0; j < line.size() - 1; j++) {
				_temp.push_back(line.at(j));
				_temp.push_back('&');
			}
			_temp.pop_back();
		}
		equals.push_back(_temp);
		_temp.clear();
	}

}

static void _Print(string model, vector<char> _output, vector<char> _input, vector<char> _map, ofstream& outfile, vector<vector<char>> equals) {

	string module = model.substr(7);
	string _node;
	for (int i = 0; i < _output.size(); i++) {
		_node += ", ";
		_node.push_back(_output.at(i));
	}
	for (int i = 0; i < _input.size(); i++) {
		_node += ", ";
		_node.push_back(_input.at(i));
	}
	string m_temp = "module " + module + "(clk, ret" + _node + ");";
	outfile << m_temp << endl;

	outfile << "input clk, ret;" << endl;


	for (int i = 0; i < _output.size(); i++) {
		string o_temp = "output ";
		o_temp.push_back(_output.at(i));
		o_temp.push_back(';');
		outfile << o_temp << endl;
	}


	for (int i = 0; i < _input.size(); i++) {
		string i_temp = "input ";
		i_temp.push_back(_input.at(i));
		i_temp.push_back(';');
		outfile << i_temp << endl;
	}


	for (int i = 0; i < _map.size(); i++) {
		string w_temp = "wire ";
		w_temp.push_back(_map.at(i));
		w_temp.push_back(';');
		outfile << w_temp << endl;
	}

	for (int i = 0; i < equals.size(); i++) {
		string a_temp = "assign ";
		for (int j = 0; j < equals.at(i).size(); j++)
			a_temp.push_back(equals.at(i).at(j));
		a_temp.push_back(';');
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

	vector<char> _output, _input, _map;

	_ProcessNode(_output, _input, _map, input, output, node);

	vector<vector<char>> equals;

	_ProcessEqual(node, equals);

	HashMap map;
	//返回数据
	map.Initialization(_map, node,_output,_input);

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
