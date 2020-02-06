#include "Interface.h"

pair<vector<vector<pair<int, int>>>, vector<int> > Interface::readGraphs()
{
    bool read_res = true;
    pair<vector<vector<pair<int, int>>>, vector<int> > result;

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

void Interface::writeAnswer(Solver solver)
{
    for (int i = 0; i < solver.all_rtn.size(); ++i)
    {
        if (solver.all_rtn[i] == 0 && solver.all_solveCorrect[i])
        {
            for (int j = 0; j < solver.all_res[i].size(); ++j)
                output << solver.all_res[i][j] + 1 << " ";
            output << endl << "The Cycle is eulerian" << endl;
        }
        if (solver.all_rtn[i] == 0 && !solver.all_solveCorrect[i])
        {
            for (int j = 0; j < solver.all_res[i].size(); ++j)
                output << solver.all_res[i][j] + 1 << " ";
            output << endl << "Error" << endl;
        }
        if (solver.all_rtn[i] == -1)
            output << "Graph is not eulerian" << endl;
        if (solver.all_rtn[i] == 1)
            output << "Graph is already eulerian" << endl;

        output << "Steps: " << solver.all_steps[i] << endl;
        output << "Time: " << solver.all_seconds[i] << endl;
        output << "*****************************************************" << endl;
    }
}
