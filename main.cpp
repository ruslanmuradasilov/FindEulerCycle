#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <time.h>
#include "OptimusGraph.h"
#include "GraphTest.h"

using namespace std;

bool isCycleEulerian(vector<int> res)
{
    set<pair<int, int>> edges;
    for (int i = 0; i < res.size() - 1; ++i)
    {
        pair<int, int> edge(res[i], res[i + 1]);
        pair<int, int> edgeReversed(res[i + 1], res[i]);
        if (!edges.emplace(edge).second || !edges.emplace(edgeReversed).second)
            return false;
    }
    return true;
}

int main()
{
    Test tests;
    pair<vector<pair<int, int>>, int> result;
    pair<vector<vector<pair<int, int>>>, vector<int> > results;
    int test_num = 1;
    for (int i = 0; i < test_num; ++i)
    {
        int nodes_num = 0, edges_num = 0;
        Test test;
        cin >> nodes_num >> edges_num;
        result = test.createTest(nodes_num, edges_num);
        results.first.push_back(result.first);
        results.second.push_back(result.second);
//    cout << result.second << endl;
//    for (int i = 0; i < result.first.size(); ++i)
//    {
//        cout << result.first[i].first << " " << result.first[i].second << endl;
//    }
    }
    tests.writeTests(test_num, "in.txt", results);

    double seconds;
    clock_t start = clock();
    Interface interface("in.txt");
    results = interface.readGraphs();
//    for (int i = 0; i < results.second.size(); ++i)
//    {
//        cout << results.second[i] << endl;
//        for (int j = 0; j < results.first[i].size(); ++j)
//        {
//            cout << results.first[i][j].first << " " << results.first[i][j].second << endl;
//        }
//    }
    vector<OptimusGraph> graphs(results.second.size());
    int rtn;
    vector<int> res;
    ofstream fcout("out.txt");
    for (int i = 0; i < results.first.size(); ++i)
    {
        graphs[i].initGraph(results.first[i], results.second[i]);
        if (!graphs[i].checkForEulerCycle())
        {
            rtn = graphs[i].recursiveComplementGraph(&res);
            if (rtn == 0)
            {
                for (int j = 0; j < res.size(); ++j)
                    fcout << res[j] + 1 << " ";
                if (isCycleEulerian(res))
                    fcout << endl << "The Cycle is eulerian" << endl;
                else
                    fcout << endl << "Error" << endl;
            } else
                fcout << "Graph is not eulerian" << endl;
        } else
            fcout << "Graph is already eulerian" << endl;
        fcout << endl << "******************************************************************************************" << endl;
        res.clear();
    }
    clock_t end = clock();
    seconds = (end - start) / CLOCKS_PER_SEC;
    fcout << "Time: " << seconds << endl;

    //1st alg
    //10000 10000 - avg of 10 - 3 sec
    //60000 60000 - 272 sec
    //70000 70000 - stack overflow

    //2nd alg
    //10000 10000 - avg of 10 - 12.8 sec
    //60000 60000 - 19 min
    //100000 100000 - 32 min


//    vector<OptimusGraph> graphs2(results.second.size());
//    int rtn2;
//    vector<int> res2;
//    for (int i = 0; i < results.first.size(); ++i)
//    {
//        graphs2[i].initGraph(results.first[i], results.second[i]);
//        if (graphs2[i].checkForEulerCycle() == false)
//        {
//            rtn2 = graphs2[i].recursiveComplementGraph(&res2);
//
//            if (rtn2 == 0)
//                for (int i = 0; i < res2.size(); ++i)
//                    fcout << res2[i] + 1 << " ";
//            else
//                fcout << "Graph is not eulerian";
//            fcout << endl;
//        } else
//            fcout << "Graph is already eulerian" << endl;
//        res2.clear();
//    }

    return 0;
}