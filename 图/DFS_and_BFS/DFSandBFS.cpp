#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void DFS(vector<vector<int>>& mat, vector<int>& visited, int n)
{
	visited[n] = 1;
	cout << n + 1 << "->";
	for (int i = 0; i < mat[n].size(); i++)
		if (mat[n][i] > 0 && visited[i] != 1)
			DFS(mat, visited, i);
}
//输入邻接矩阵,利用递归实现DFS

void DFSTraversal(vector<vector<int>>& mat)
{
	int n = mat.size();
	vector<int> visited(n, 0);
	for (int i = 0; i < n; i++)
		if (!visited[i])
			DFS(mat, visited, i);
}


void BFSTraversal(vector<vector<int>>& mat)
{
	int n = mat.size();
	vector<int> visited(n, 0);
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			q.push(i);
			visited[i] = 1;
			while (!q.empty())
			{
				int cur = q.front();
				q.pop();
				cout << cur+1 << "->";
				//cur为当前已经遍历结点
				for (int j = 0; j < mat[cur].size(); j++)
				{
					if (mat[cur][j] > 0 && !visited[j])
					{
						q.push(j);
						visited[j] = 1;
					}
				}
			}
		}
	}
}
//利用队列实现BFS算法，输入邻接矩阵

int main()
{
	vector<vector<int>> mat =
	{
		{0,1,1,0,1},
		{1,0,1,1,0},
		{1,1,0,0,0},
		{0,1,0,0,1},
		{1,0,0,1,0}
	};
	vector<int> visi(5, 0);
	DFS(mat, visi, 0);
	//BFSTraversal(mat);
	return 0;
}