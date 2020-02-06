#include "Graph.h"

using namespace std;

void Graph::initGraph(vector<pair<int, int>> edges, int n)
{
    this->n = n;

    for (int i = 0; i < n; ++i)
    {
        deg.push_back(0);
        steps_counter++;
    }
    for (int i = 0; i < n; ++i)
    {
        matrix.push_back(deg);
        steps_counter++;
    }


    for (int i = 0; i < edges.size(); ++i)
    {
        matrix[edges[i].first][edges[i].second]++;
        matrix[edges[i].second][edges[i].first]++;
        steps_counter++;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            deg[i] += matrix[i][j];
            steps_counter++;
        }

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
    {
        if (deg[i] % 2 == 1)
            oddVertex++;
        steps_counter++;
    }

    return oddVertex < 2;
}

void Graph::findEulerCycle(vector<int> *res)
{
    int first = 0;//стартовая вершина
    while (!deg[first])//проверка стартовой вершины на изолированность
    {
        first++;
        steps_counter++;
    }

    stack<int> st;
    st.push(first);
    while (!st.empty())
    {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
        {
            steps_counter++;
            if (matrix[v][i])// нашли ребро, по которому ещё не прошли
                break;
        }
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

int Graph::graphCompletion(vector<int> *res)
{
    int p = 0, pp = 0;
    bool check;
    while (true)
    {
        check = checkForEulerCycle();//проверяем граф на эйлеровость
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
                    pp = 0, p = 0;
                    for (int j = i + 1; j < n; ++j)
                    {
                        steps_counter++;
                        if (deg[j] % 2 == 1 && matrix[i][j] == 0 && j != i)//находим еще одну нечвершину, с которой нет смежного ребра и добавляем его
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
                pp = 0;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = i + 1; j < n; ++j)
                    {
                        steps_counter++;
                        if (matrix[i][j] == 0 && j != i)//то добавляем любое ребро
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
                        break;
                }
                if (pp == 0)//граф полный
                    return -1;
            }
        }
    }
}

bool Graph::isCycleEulerian(vector<int> res)
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
