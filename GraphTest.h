#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class Test
{
public:
    bool correctEdge(pair<int, int> edge, vector<pair<int, int>> edges)
    {
        if (edge.first == edge.second)
            return false;
        for (auto i : edges)
        {
            if (i.first == edge.first && i.second == edge.second)
                return false;
            if (i.first == edge.second && i.second == edge.first)
                return false;
        }

        return true;
    }

    pair<vector<pair<int, int>>, int> createTest(int nodes_num, int edges_num)
    {
        int temp;
        srand(time(NULL));
        vector<pair<int, int>> edges;
        pair<vector<pair<int, int>>, int> result;
        for (int i = 0; i < edges_num; ++i)
        {
            while (true)
            {
                pair<int, int> new_edge;
                new_edge.first = rand() % nodes_num + 1;
                new_edge.second = rand() % nodes_num + 1;
                if (new_edge.first > new_edge.second)
                {
                    temp = new_edge.first;
                    new_edge.first = new_edge.second;
                    new_edge.second = temp;
                }
                if (correctEdge(new_edge, edges))
                {
                    edges.push_back(new_edge);
                    break;
                }
            }
        }
        result.first = edges;
        result.second = nodes_num;
        return result;
    }

    void writeTests(int test_num, const char *path, pair<vector<vector<pair<int, int>>>, vector<int> > graphs)
    {
        ofstream output("in.txt");
        for (int i = 0; i < test_num; ++i)
        {
            output << graphs.second[i] << endl;
            for (int j = 0; j < graphs.first[i].size(); ++j)
                output << graphs.first[i][j].first << " " << graphs.first[i][j].second << endl;

            if (i == test_num - 1)
                output << "-1 -1";
            else
                output << "-1 -1" << endl;
        }
        output.close();
    }
};
