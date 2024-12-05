#include<iostream>
#include<vector>
using namespace std;

//递归找最终父节点
int FindParent(vector<int>& parent, int index)
{
	if (parent[index] != index)
		parent[index] = FindParent(parent, parent[index]);
	return parent[index];
}

//并集使得index1的最终父节点的父节点为index2的最终父节点
void Union(vector<int>& parent, int index1, int index2)
{
	parent[FindParent(parent, index1)] = FindParent(parent, index2);
}

int main()
{
	vector<vector<int>> edges = { {1,2},{2,3},{3,4},{1,4},{1,5} };
	//邻接边矩阵
	int n = edges.size();
	vector<int> parent(n + 1);
	for (int i = 1; i <= n; i++)
		parent[i] = i;
	//开始设置父节点为自己
	for (auto& edge : edges)
	{
		int node1 = edge[0], node2 = edge[1];
		if (FindParent(parent, node1) != FindParent(parent, node2))
			Union(parent, node1, node2);
		else cout << edge[0]<<' '<<edge[1];
	}
}