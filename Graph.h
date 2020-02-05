#pragma once
#include <vector>
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

    virtual int recursiveComplementGraph(vector<int> *);
};