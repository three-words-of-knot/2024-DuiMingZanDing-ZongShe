#pragma once
#include<iostream>
#include<vector>
#include "Hash.h"
using namespace std;
#ifndef MYMETHOD_H
#define MYMETHOD_H

void AFAP(HashMap _map);

void ALAP(HashMap _map);

void ToCycle(HashMap _map);

void FromCycle(HashMap _map);

vector<vector<int>> SPUsing(HashMap map, int& max, int& num1, int& num2, int& num3);
#endif 
