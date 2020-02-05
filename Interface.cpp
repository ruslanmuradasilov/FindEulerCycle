#include "Interface.h"

pair<vector<vector<pair<int, int>>>, vector<int> > Interface::readGraphs()
{
    bool read_res = true;
    pair<vector<vector<pair<int, int>>>, vector<int> >  result;

    vector<int> nodes_nums;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> graphs;

    for (int i = 0; !input.eof(); i++)
    {
        int a, b;

        if (read_res == true)
        {
            input >> a;
            nodes_nums.push_back(a);
            read_res = false;
            continue;
        }
        input >> a >> b;
        if (a < 0 && b < 0)
        {
            read_res = true;
            graphs.push_back(edges);
            edges.clear();
            continue;
        }
        edges.emplace_back(a - 1, b - 1);
    }
    result.first = graphs;
    result.second = nodes_nums;
    return result;
}

vector<int> Interface::readExpectedResults(const char *path)
{
    ifstream f(path);
    vector<int> expected_results;
    for (int i = 0; !input.eof(); i++)
    {
        int a;
        f >> a;
        expected_results.push_back(a);
    }
    f.close();
    return expected_results;
}