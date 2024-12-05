#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
const int INF = 1e6;

void Dijkstra(int n, int s, vector<vector<int>>& G, vector<bool>& vis, vector<int>& d, vector<int>& pre)
{
    /*
     *   n:        顶点个数
     *   s:        源点
     *   G:        图的邻接矩阵
     * vis:        标记顶点是否已被访问
     *   d:        存储源点s到达其它顶点的最短距离
     * pre:        最短路径中v的前驱结点
     */
    fill(vis.begin(), vis.end(), 0);
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    for (int i = 0; i < n; i++)
        pre[i] = i;
    for (int i = 0; i < n; i++)
    {
        int u = -1; 
        int MIN = INF;
        for(int j=0;j<n;j++)
            if (!vis[j] && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        if (u == -1) return;
        vis[u] = 1;
        for(int v=0;v<n;v++)
            if (!vis[v] && G[u][v] != INF && d[u] + G[u][v] < d[v])
            {
                d[v] = d[u] + G[u][v];
                pre[v] = u;
            }
    }
}

void DFSPrint(int s, int v, vector<int>& pre)
{
    if (v == s)
    {
        cout << s << " ";
        return;
    }
    DFSPrint(s, pre[v], pre);
    cout << v << " ";
}

int main()
{
    int n = 6;
    vector<vector<int>> G = { 
        {  0,  4,INF,INF,  1,  2},
        {  4,  0,  6,INF,INF,  3},
        {INF,  6,  0,  6,INF,  5},
        {INF,INF,  6,  0,  4,  5},
        {  1,INF,INF,  4,  0,  3},
        {  2,  3,  5,  5,  3,  0} 
    };
    vector<bool> vis(n);
    vector<int> d(n);
    vector<int> pre(n);
    Dijkstra(n, 0, G, vis, d, pre);
    for (int i = 0; i < n; ++i)
    {
        cout << "the shortest path " << i << " is: " << d[i] << endl;
    }
    cout << endl;

    // v = 2: 0->5->2  cost = 2 + 5 = 7
    // v = 3: 0->4->3  cost = 1 + 4 = 5
    int v = 2;
    DFSPrint(0, v, pre);
    cout << endl << "cost = " << d[v] << endl;

	return 0;
}