#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <thread>
#include <memory>
#include <algorithm>

using std::ostream;
using std::cout;
using std::cin;
using std::cerr;
using std::clog;
using std::endl;
using std::setw;

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::to_string;
using std::stoi;
using std::swap;

using std::shared_ptr;

using std::exception;
using std::out_of_range;

const uint8_t Size = 10;
const string Letters = "ABCDEFGHIJ";
const uint8_t ShipRules[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

static vector<string> Split(string str, string sep = " ", bool RemoveEmptyString = true)
{
	str += sep;
	vector<string> vec;

	size_t pos;
	while ((pos = str.find(sep)) != string::npos)
	{
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + sep.size()); // Стираем полученный фрагмент
	}

	if (RemoveEmptyString)
		vec.erase(std::remove(vec.begin(), vec.end(), ""), vec.end());

	return vec;
}