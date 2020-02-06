#pragma once

#include <ctime>
#include "OptimusGraph.h"

using namespace std;

class Solver
{
public:
    vector<int> all_rtn;
    vector<vector<int> > all_res;
    vector<double> all_seconds;
    vector<bool> all_solveCorrect;
    vector<unsigned long long> all_steps;


    void solve(pair<vector<vector<pair<int, int>>>, vector<int> > results)
    {
        vector<Graph> graphs(results.second.size());
        int rtn;
        vector<int> res;
        double seconds;
        bool solveCorrect;
        unsigned long long steps;
        for (int i = 0; i < results.first.size(); ++i)
        {
            clock_t start = clock();
            graphs[i].initGraph(results.first[i], results.second[i]);
            if (!graphs[i].checkForEulerCycle())
            {
                rtn = graphs[i].graphCompletion(&res);
                if (rtn == 0)
                    solveCorrect = graphs[i].isCycleEulerian(res);
            } else
                rtn = 1;
            clock_t end = clock();
            seconds = (end - start) / CLOCKS_PER_SEC;
            steps = graphs[i].steps_counter;
            all_rtn.push_back(rtn);
            all_res.push_back(res);
            all_seconds.push_back(seconds);
            all_solveCorrect.push_back(solveCorrect);
            all_steps.push_back(steps);
            res.clear();
        }
    }

    void optimusSolve(pair<vector<vector<pair<int, int>>>, vector<int> > results)
    {
        vector<OptimusGraph> graphs(results.second.size());
        int rtn;
        vector<int> res;
        double seconds;
        bool solveCorrect;
        unsigned long long steps;
        for (int i = 0; i < results.first.size(); ++i)
        {
            clock_t start = clock();
            graphs[i].initGraph(results.first[i], results.second[i]);
            if (!graphs[i].checkForEulerCycle())
            {
                rtn = graphs[i].graphCompletion(&res);
                if (rtn == 0)
                    solveCorrect = graphs[i].isCycleEulerian(res);
            } else
                rtn = 1;
            clock_t end = clock();
            seconds = (end - start) / CLOCKS_PER_SEC;
            steps = graphs[i].steps_counter;
            all_rtn.push_back(rtn);
            all_res.push_back(res);
            all_seconds.push_back(seconds);
            all_solveCorrect.push_back(solveCorrect);
            all_steps.push_back(steps);
            res.clear();
        }
    }
};