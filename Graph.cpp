#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Graph.h"

using namespace std;

void Graph::initGraph(vector<pair<int, int>> edges, int n)
{
    this->n = n;

    for (int i = 0; i < n; ++i)
        deg.push_back(0);
    for (int i = 0; i < n; ++i)
        matrix.push_back(deg);

    for (int i = 0; i < edges.size(); ++i)
    {
        matrix[edges[i].first][edges[i].second]++;
        matrix[edges[i].second][edges[i].first]++;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            deg[i] += matrix[i][j];
}

void Graph::print()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

bool Graph::checkForEulerCycle()
{
    int oddVertex = 0;
    for (int i = 0; i < n; ++i)
        if (deg[i] % 2 == 1)
            oddVertex++;

    return oddVertex == 2 || oddVertex == 0 ? true : false;
}

void Graph::findEulerCycle(vector<int> *res)
{
    int first = 0;//стартовая вершина
    while (!deg[first])//проверка стартовой вершины на изолированность
        first++;

    stack<int> st;
    st.push(first);
    while (!st.empty())
    {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (matrix[v][i])// нашли ребро, по которому ещё не прошли
                break;
        if (i == n)
        {
            st.pop();// не нашлось инцидентных вершине v рёбер, по которым ещё не прошли
            (*res).push_back(v);
        } else
        {
            --matrix[v][i];
            --matrix[i][v];
            st.push(i);// добавили новую вершину в стек
        }
    }
}

int Graph::recursiveComplementGraph(vector<int> *res)
{
    int p = 0;
    bool check = checkForEulerCycle();//проверяем граф на эйлеровость
    if (check)//если эйлеров
    {
        findEulerCycle(res);
        return 0;
    } else//если неэйлеров
    {
        for (int i = 0; i < n; ++i)
        {
            if (deg[i] % 2 == 1)//ищем нечвершину
            {
                int pp = 0;
                for (int j = 0; j < n && j != i; ++j)
                {
                    if (deg[j] % 2 == 1 &&
                        matrix[i][j] == 0)//находим еще одну нечвершину, с которой нет смежного ребра и добавляем его
                    {
                        matrix[i][j]++;
                        matrix[j][i]++;
                        deg[i]++;
                        deg[j]++;
                        pp = 1;
                        break;
                    }
                }
                if (pp == 1)
                {
                    p = 1;//добавили ребро
                    break;
                }
            }
        }
        if (p == 0)//если не нашли две нечвершины, не соединенные ребром
        {
            int pp = 0;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n && j != i; ++j)
                    if (matrix[i][j] == 0)//то добавляем любое ребро
                    {
                        matrix[i][j]++;
                        matrix[j][i]++;
                        deg[i]++;
                        deg[j]++;
                        pp = 1;
                        break;
                    }
                if (pp == 1)
                    break;
            }
            if (pp == 0)//граф полный
                return -1;
        }
        recursiveComplementGraph(res);
    }
}
