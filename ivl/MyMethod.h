#pragma once
#include<iostream>
#include<vector>
using namespace std;
#ifndef MYMETHOD_H
#define MYMETHOD_H

void AFAP(vector<vector<int>> map_node, vector<char> map_name, vector<int> end);

void ALAP(vector<vector<int>> map_node, vector<char> map_name, vector<int> end);

void InfoToCycle(vector<vector<int>> map_node, vector<char> map_name, vector<int> end, int OR, int AND, int NO);

#endif 
