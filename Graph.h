#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Interface.h"

using namespace std;

class Graph
{
protected:
    int n;//количество вершин в графе
    vector<vector<int> > matrix;//матрица смежности
    vector<int> deg;//степени каждой вершины

public:
    virtual void initGraph(vector<pair<int, int>>, int);

    virtual void print();

    bool checkForEulerCycle();

    virtual void findEulerCycle(vector<int> *);

    virtual int graphСompletion(vector<int> *);

    unsigned long long steps_counter = 0;
};