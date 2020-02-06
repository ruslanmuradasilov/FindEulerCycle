#include "OptimusGraph.h"

using namespace std;

void OptimusGraph::initGraph(vector<pair<int, int>> edges, int n)
{
    this->n = n;
    this->edges = edges;

    //nodes = vector<Node>(n);
    deg = vector<int>(n);

    for (auto i : edges)
        for (int j = 0; j < n; j++)
        {
            if (i.first == j || i.second == j)
                deg[j]++;
            steps_counter++;
        }
}

void OptimusGraph::print()
{
    for (auto i : edges)
        cout << i.first << " " << i.second << endl;
}

void OptimusGraph::findEulerCycle(vector<int> *res)
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
        int i, p = 0, k = 0;
        for (i = 0; i < n; i++)
        {
            for (auto j : edges)
            {
                if (j.first == v)
                {
                    k = j.second;
                    p = 1;
                    break;
                }
                if (j.second == v)
                {
                    k = j.first;
                    p = 1;
                    break;
                }
                steps_counter++;
            }
            if (p == 1)
                break;
        }
        if (i == n)
        {
            st.pop();// не нашлось инцидентных вершине v рёбер, по которым ещё не прошли
            (*res).push_back(v);
        } else
        {
            for (int j = 0; j < edges.size(); j++)
            {
                steps_counter++;
                if ((edges[j].first == k && edges[j].second == v) || (edges[j].first == v && edges[j].second == k))
                    edges.erase(edges.begin() + j);
            }
            st.push(k);// добавили новую вершину в стек
        }
    }
}


bool OptimusGraph::edgeExists(int i, int j)
{
    for (auto k : edges)
    {
        steps_counter++;
        if ((k.first == i && k.second == j) || (k.first == j && k.second == i))
            return true;
    }
    return false;
}

int OptimusGraph::graphCompletion(vector<int> *res)
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
                    for (int j = i + 1; j < n; j++)
                    {
                        steps_counter++;
                        if (deg[j] % 2 == 1 && j != i)//находим еще одну нечвершину,
                        {
                            if (edgeExists(i, j))//с которой нет смежного ребра
                                continue;
                            edges.emplace_back(i, j);//и добавляем его
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
                        if(j != i)
                        {
                            if (edgeExists(i, j))
                                continue;
                            edges.emplace_back(i, j);//то добавляем любое ребро
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


//void OptimusGraph::initGraph(vector<pair<int, int>> edges_input, int n)
//{
//    this->n = n;
//    for (int i = 0; i < edges_input.size(); ++i)
//        this->edges.insert(edges_input[i]);
//
//
//    //nodes = vector<Node>(n);
//    deg = vector<int>(n);
//
//    for (auto i : edges)
//        for (int j = 0; j < n; j++)
//            if (i.first == j || i.second == j)
//                deg[j]++;
//}

//void OptimusGraph::findEulerCycle(vector<int> *res)
//{
//    int first = 0;//стартовая вершина
//    while (!deg[first])//проверка стартовой вершины на изолированность
//        first++;
//
//    stack<int> st;
//    st.push(first);
//    while (!st.empty())
//    {
//        int v = st.top();
//        int i, p = 0, k = 0;
//        for (i = 0; i < n; i++)
//        {
//            for (auto j : edges)
//            {
//                if (j.first == v)
//                {
//                    k = j.second;
//                    p = 1;
//                    break;
//                }
//                if (j.second == v)
//                {
//                    k = j.first;
//                    p = 1;
//                    break;
//                }
//            }
//            if (p == 1)
//                break;
//        }
//        if (i == n)
//        {
//            st.pop();// не нашлось инцидентных вершине v рёбер, по которым ещё не прошли
//            (*res).push_back(v);
//        } else
//        {
//            pair<int, int> key(k, v);
//            pair<int, int> keyReversed(v, k);
//
//            if (edges.find(key) == edges.end())
//                edges.erase(edges.find(keyReversed));
//            else
//                edges.erase(edges.find(key));
//            st.push(k);// добавили новую вершину в стек
//        }
//    }
//}

//int OptimusGraph::recursiveComplementGraph(vector<int> *res)
//{
//    int p = 0;
//    bool check = checkForEulerCycle();//проверяем граф на эйлеровость
//    if (check)//если эйлеров
//    {
//        findEulerCycle(res);
//        return 0;
//    } else//если неэйлеров
//    {
//        for (int i = 0; i < n; ++i)
//        {
//            if (deg[i] % 2 == 1)//ищем нечвершину
//            {
//                int pp = 0;
//                for (int j = 0; j < n && j != i; j++)
//                {
//                    if (deg[j] % 2 == 1)//находим еще одну нечвершину,
//                    {
//                        pair<int, int> edge(i, j);
//                        pair<int, int> edgeReversed(j, i);
//                        if (!edges.emplace(edge).second || !edges.emplace(edgeReversed).second)//и добавляем его
//                            continue;
//                        deg[i]++;
//                        deg[j]++;
//                        pp = 1;
//                        break;
//                    }
//                }
//                if (pp == 1)
//                {
//                    p = 1;//добавили ребро
//                    break;
//                }
//            }
//        }
//        if (p == 0)//если не нашли две нечвершины, не соединенные ребром
//        {
//            int pp = 0;
//            for (int i = 0; i < n; ++i)
//            {
//                for (int j = 0; j < n && j != i; ++j)
//                {
//                    pair<int, int> edge(i, j);
//                    pair<int, int> edgeReversed(j, i);
//                    if (!edges.emplace(edge).second || !edges.emplace(edgeReversed).second)//то добавляем любое ребро
//                        continue;
//                    deg[i]++;
//                    deg[j]++;
//                    pp = 1;
//                    break;
//                }
//                if (pp == 1)
//                    break;
//            }
//            if (pp == 0)//граф полный
//                return -1;
//        }
//        recursiveComplementGraph(res);
//    }
//}