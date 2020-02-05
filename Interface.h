#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Interface
{
    ifstream input;
    ofstream output;

public:
    Interface(const string &input_path) : input(input_path)
    {}

    pair<vector<vector<pair<int, int>>>, vector<int> > readGraphs();

    vector<int> readExpectedResults(const char *);
};

