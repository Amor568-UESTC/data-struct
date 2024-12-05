#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct edge
{
	int u, v;
	int weight;
};
vector<int> father; //记录个节点的“父亲”
vector<int> result; //存储最后获得的边的权

bool compare(const edge& a, const edge& b)
{
	return a.weight < b.weight;
}

int findfather(int a)
{
	while (a != father[a])
		a = father[a];
	return a;
}

void kruskal(int n, vector<edge>& Edge)
{
	father.resize(n);
	sort(Edge.begin(), Edge.end(), compare);
	for (int i = 0; i < n; i++)
		father[i] = i;
	//初始爹为ziji
	for (int i = 0; i < Edge.size() && result.size() < n - 1; i++)
	{
		int u = Edge[i].u;
		int v = Edge[i].v;
		if (findfather(u) != findfather(v)) //判断父节点是否相同
		{									//查看是否成环 
			result.push_back(Edge[i].weight);
			father[findfather(u)] = father[findfather(v)];
			//两点并入一个集合中
		}
	}
	if (result.size() != n - 1)
	{
		cout << result.size() << "no !" << endl;
		return;
	}
	else
	{
		cout << "edges as follow: " << endl;
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;
	}
}

int main()
{
	int n, m;
	cout << "enter num of vertexes: ";
	cin >> n;
	cout << "enter num of edges: ";
	cin >> m;
	vector<edge> Edge(m);
	cout << "discribe edges: " << endl;
	for (int i = 0; i < m; i++)
		cin >> Edge[i].u >> Edge[i].v >> Edge[i].weight;
	kruskal(n, Edge);
	return 0;
}