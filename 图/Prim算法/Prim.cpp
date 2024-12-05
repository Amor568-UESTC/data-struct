#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

struct element
{
	int lowcost, adjvex;
	//adjvex作为储存目前的有的点对应的最短的距离的点
	//lowcost储存对应两点的距离（若为0，则被保存进目前有的点里）
};

//找到目前顶点到其他顶点的最短距离，输出最短距离相应的顶点
int MinEdge(vector<element>& shortEdge, int vertexNum)
{
	int index = -1;
	int v;
	for(v=0;v<vertexNum;v++)
		if (shortEdge[v].lowcost > 0)
		{
			index = v;
			break;
		}
	//找到第一个lowcost不为0的点(为0则已被收入)
	for (v = v + 1; v < vertexNum; v++)
		if (shortEdge[v].lowcost > 0 && shortEdge[v].lowcost < shortEdge[index].lowcost)
			index = v;
	return index;	//返回最小距离点
}

template<class Data>
class MGraph
{
private:
	vector<Data> vertex;
	vector<vector<int>> arc;
	int vertexNum, arcNum;
public:
	MGraph(vector<Data>& a, const int& n, const int& e);
	friend void Prim(MGraph<char> MG);
};

//n个顶点，e条边，a为顶点数组
template<class Data>
MGraph<Data>::MGraph(vector<Data>& a, const int& n, const int& e)
{
	int i, j, w = 0;
	vertexNum = n, arcNum = e;
	vertex.resize(n);
	arc.resize(n, vector<int>(n, 255));
	//255表示无穷远未连接
	for (int i = 0; i < n; i++)
		vertex[i] = a[i];
	for (int k = 0; k < arcNum; k++)
	{
		cout << "please enter 2 vertexes: ";
		cin >> i >> j;
		cout << "please enter weight of edge: ";
		cin >> w;
		arc[i][j] = arc[j][i] = w;
	}
}

void Prim(MGraph<char> MG)
{
	int j;
	int v = 0; //从0开始进入结点
	vector<element> shortEdge(MG.vertexNum);
	for (int i = 0; i < MG.vertexNum; i++)
	{
		shortEdge[i].adjvex = v;
		shortEdge[i].lowcost = MG.arc[v][i];
	}
	shortEdge[v].lowcost = 0;
	//遍历全部结点查看，0表示已经收入
	for (int k = 1; k < MG.vertexNum; k++)	//循环“顶点数-1”次，因为每次增加一条边，刚好增加“顶点数-1”条边 
	{
		j = MinEdge(shortEdge, MG.vertexNum);
		cout << "<" << shortEdge[j].adjvex << "," << j << ">" << shortEdge[j].lowcost << endl;
		shortEdge[j].lowcost = 0;
		for(int i=0;i<MG.vertexNum;i++)		
			if (MG.arc[i][j] < shortEdge[i].lowcost)	//此时shortEdge[i].lowcost还表示到上一个点距离
			{											//如果到j更小取而代之即可，维护shortEdge
				shortEdge[i].lowcost = MG.arc[i][j];
				shortEdge[i].adjvex = j;
			}
	}
}

int main()
{
	vector<char> ch = { 'a','b','c','d','e','f' };
	MGraph<char> MG(ch, 6, 9);
	cout << "the min tree process is: " << endl;
	Prim(MG);
	cout << endl;
	system("pause");
	return 0;
}