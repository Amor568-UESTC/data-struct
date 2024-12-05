#include<iostream>
#include<vector>
using namespace std;

//�ݹ������ո��ڵ�
int FindParent(vector<int>& parent, int index)
{
	if (parent[index] != index)
		parent[index] = FindParent(parent, parent[index]);
	return parent[index];
}

//����ʹ��index1�����ո��ڵ�ĸ��ڵ�Ϊindex2�����ո��ڵ�
void Union(vector<int>& parent, int index1, int index2)
{
	parent[FindParent(parent, index1)] = FindParent(parent, index2);
}

int main()
{
	vector<vector<int>> edges = { {1,2},{2,3},{3,4},{1,4},{1,5} };
	//�ڽӱ߾���
	int n = edges.size();
	vector<int> parent(n + 1);
	for (int i = 1; i <= n; i++)
		parent[i] = i;
	//��ʼ���ø��ڵ�Ϊ�Լ�
	for (auto& edge : edges)
	{
		int node1 = edge[0], node2 = edge[1];
		if (FindParent(parent, node1) != FindParent(parent, node2))
			Union(parent, node1, node2);
		else cout << edge[0]<<' '<<edge[1];
	}
}