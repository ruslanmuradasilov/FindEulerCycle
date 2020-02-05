#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include "Graph.h"

using namespace std;

class OptimusGraph : public Graph
{
private:
    /*struct Node
    {
        int number;
        vector<Node *> neighs;
    };*/

    //vector<Node> nodes;
    vector<pair<int, int>> edges;

public:
    void initGraph(vector<pair<int, int>>, int) override;

    void print() override;

    void findEulerCycle(vector<int> *) override;

    bool edgeExists(int, int);

    int recursiveComplementGraph(vector<int> *) override;
};