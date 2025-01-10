#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<sstream>

#include"MyMethod.h"
#include"Hash.h"

using namespace std;

#define NAME "test"

static void _Print(vector<vector<int>> vec,HashMap map,ofstream &outfile,int A,int B,int C,int D) {


	vector<string> vec1;
	outfile << "Min" << endl;
	string A_string;
	for (int i = 1; i <=A+1; i++) {
		string temp;
		temp += "XA";
		temp += to_string(i);
		vec1.push_back(temp);
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
				string tempp;
				tempp += "X";
				tempp += map.nodeName.at(i);
				tempp += to_string(j);
				vec1.push_back(tempp);

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

	outfile << "Binary" << endl;

	for (int i = 0; i < vec1.size(); i++) {
		outfile << vec1.at(i) << endl;
	}

	outfile << "End" << endl;
}

static void _Read(ifstream& src,vector<string> &module,vector<string> &input, vector<string> &output, vector<string>&assign) {

	string line;
	while (getline(src, line)) {
		char first = line.front();
		switch (first) {
		case 'm':
			module.push_back(line);
			break;
		case 'i':
			input.push_back(line);
			break;
		case 'o':
			output.push_back(line);
			break;
		case 'w':
			break;
		case 'a':
			assign.push_back(line);
			break;
		}
		line.clear();
	}
}

static void _Process(vector<string> assign,vector<string> &result) {

	for (int i = 0; i < assign.size(); i++) {

		string temp = assign.at(i);
		string str;
		istringstream iss(temp);
		vector<string> vec;
		string answer;
		while (iss >> str)
			vec.push_back(str);

		str = vec.at(1);
		answer += str.at(0);
		char third = str.at(2);	
		if (third == '~') {
			answer += str.at(3);
			answer += '~';
		}
		else {		

			char forth = str.at(3);

			for (int j = 2; j < str.size(); j += 2)
				answer += str.at(j);
			answer += forth; 
		}

		result.push_back(answer);
	}
}

static void _Printf(ofstream& outfile, vector<string> result, vector<string> module, vector<string>input,vector<string> output) {

	string str,temp;
	vector<string> vec;
	istringstream iss1(module.at(0));
	while (iss1 >> str)
		vec.push_back(str);
	str = vec.at(1);

	char delimiter = '(';
	size_t pos = str.find(delimiter);

	if (pos != string::npos) {
		string firstPart = str.substr(0, pos);
		string secondPart = str.substr(pos + 1);
		str = firstPart;
	}
	else {
		cout << "出现未知问题，需要修复" << endl;
	}

	temp += ".model ";
	temp += str;
	outfile << temp << endl;
	str.clear();
	vec.clear();
	temp.clear();

	temp += ".inputs";
	for (int i = 0; i < input.size(); i++) {
		istringstream iss2(input.at(i));
		while (iss2 >> str)
			vec.push_back(str);
		str = vec.at(1);
		str.pop_back();
		temp += " ";
		temp += str;
		str.clear();
		vec.clear();
	}
	outfile << temp << endl;
	temp.clear();

	temp += ".outputs";
	for (int i = 0; i < output.size(); i++) {
		istringstream iss3(output.at(i));
		while (iss3 >> str)
			vec.push_back(str);
		str = vec.at(1);
		str.pop_back();
		temp += " ";
		temp += str;
		str.clear();
		vec.clear();
	}
	outfile << temp << endl;
	temp.clear();

	for (int i = 0; i < result.size(); i++) {
		temp += ".names";
		int count = -1;
		switch (result.at(i).back()) {
		case '~':
			for (int j = result.at(i).size() - 2; j >=0 ; j--) {
				temp += " ";
				temp += result.at(i).at(j);
			}
			outfile << temp << endl;
			temp.clear();
			outfile << "0 1" << endl;
			break;
		case '|':
			for (int j = result.at(i).size() - 2; j >= 0; j--) {
				count++;
				temp += " ";
				temp += result.at(i).at(j);
			}
			outfile << temp << endl;
			temp.clear();
			for (int j = 0; j < count; j++) {
				for (int k = 0; k < count; k++) {
					if (k == j)
						temp += "1";
					else
						temp += "-";
				}
				temp += " 1";
				outfile << temp << endl;
				temp.clear();
			}
			break;
		case '&':
			for (int j = result.at(i).size() - 2; j >= 0; j--) {
				count++;
				temp += " ";
				temp += result.at(i).at(j);
			}
			outfile << temp << endl;
			temp.clear();
			for (int j = 0; j < count; j++)
				temp += "1";
			temp += " 1";
			outfile << temp << endl;
			temp.clear();
			break;
		}
	}

	outfile << ".end" << endl;
}

void Transformer(HashMap map) {

	int num1, num2, num3;
	num1 = num2 = num3 = 0;
	int temp = 0;
	vector<vector<int>> vec;
	vec = SPUsing(map,temp,num1,num2,num3);

	string outputName;
	outputName = NAME;
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

void UnTransform() {
	string inputName, outputName, s_temp;
	inputName = outputName = NAME;
	cout << "请写入输入文件名字（默认为test）:" << endl;
	getline(cin, s_temp);
	if (!s_temp.empty())
		inputName = s_temp;
	inputName += ".v";
	cout << "请写入输出文件名字（默认为test）:"<<endl;
	getline(cin, s_temp);
	if (!s_temp.empty())
		outputName = s_temp;
	outputName += ".blif";


	ifstream src(inputName);
	ofstream outfile(outputName);
	if (src.is_open())
		cout << "输入文件成功打开" << endl;
	else
		cout << "输入文件打开失败，请查看源文件路径下是否存在" << inputName << "文件" << endl;

	vector<string> module, input, output, assign;
	_Read(src,module,input,output,assign);

	vector<string> result;
	_Process(assign,result);


	if (outfile.is_open()) {
		_Printf(outfile,result,module,input,output);
		cout << "文件打印完成" << endl;
	}
	else
		cout << "verliog文件未成功打开，请检查写入部分" << endl;
	outfile.close();
	src.close();

}