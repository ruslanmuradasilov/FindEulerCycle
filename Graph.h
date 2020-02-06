#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <stack>

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

    virtual int graphCompletion(vector<int> *);

    bool isCycleEulerian(vector<int>);

    unsigned long long steps_counter = 0;
};