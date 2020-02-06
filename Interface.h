#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Solver.h"

using namespace std;

class Interface
{
    ifstream input;
    ofstream output;

public:
    explicit Interface(const string &input_path, const string &output_path) : input(input_path), output(output_path)
    {}

    pair<vector<vector<pair<int, int>>>, vector<int> > readGraphs();

    vector<int> readExpectedResults(const char *);

    void writeAnswer(Solver);
};

