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
        int nodes_num = 10000, edges_num = 10000;
        Test test;
        //cin >> nodes_num >> edges_num;
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
    clock_t start, end;
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
        start = clock();
        graphs[i].initGraph(results.first[i], results.second[i]);
        fcout << endl << "Steps: " << graphs[i].steps_counter << endl;
        if (!graphs[i].checkForEulerCycle())
        {
            rtn = graphs[i].graphCompletion(&res);
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
        end = clock();
        seconds = (end - start) / CLOCKS_PER_SEC;
        fcout << endl << "Steps: " << graphs[i].steps_counter << endl;
        fcout << "Time: " << seconds << endl;
        fcout << "******************************************************************************************" << endl;
        res.clear();
    }

    //1st alg
    //10000 10000 - avg of 10 - 3 sec -> 1 sec, 308380219 (308 mln = 100 mln to init)
    //60000 60000 - 272 sec -> 87 sec, 9311878367 (9,3 mlrd)
    //70000 70000 - terminate called after throwing an instance of 'std::bad_alloc'
    //Complexity: O(3*n^2)

    //2nd alg
    //10000 10000 - avg of 10 - 12.8 sec -> 5.4 sec, 670 mln = 100 mln to init
    //60000 60000 - 19 min -> 132 sec, 13793837875 (13,7 mlrd); 181 sec, 21093952423 (21 mlrd)
    //100000 100000 - 32 min -> 499 sec (8,3 min), 59911117855 (59 mlrd)
    //Complexity: O(6*n^2)

    return 0;
}