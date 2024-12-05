#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

struct element
{
	int lowcost, adjvex;
	//adjvex��Ϊ����Ŀǰ���еĵ��Ӧ����̵ľ���ĵ�
	//lowcost�����Ӧ����ľ��루��Ϊ0���򱻱����Ŀǰ�еĵ��
};

//�ҵ�Ŀǰ���㵽�����������̾��룬�����̾�����Ӧ�Ķ���
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
	//�ҵ���һ��lowcost��Ϊ0�ĵ�(Ϊ0���ѱ�����)
	for (v = v + 1; v < vertexNum; v++)
		if (shortEdge[v].lowcost > 0 && shortEdge[v].lowcost < shortEdge[index].lowcost)
			index = v;
	return index;	//������С�����
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

//n�����㣬e���ߣ�aΪ��������
template<class Data>
MGraph<Data>::MGraph(vector<Data>& a, const int& n, const int& e)
{
	int i, j, w = 0;
	vertexNum = n, arcNum = e;
	vertex.resize(n);
	arc.resize(n, vector<int>(n, 255));
	//255��ʾ����Զδ����
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
	int v = 0; //��0��ʼ������
	vector<element> shortEdge(MG.vertexNum);
	for (int i = 0; i < MG.vertexNum; i++)
	{
		shortEdge[i].adjvex = v;
		shortEdge[i].lowcost = MG.arc[v][i];
	}
	shortEdge[v].lowcost = 0;
	//����ȫ�����鿴��0��ʾ�Ѿ�����
	for (int k = 1; k < MG.vertexNum; k++)	//ѭ����������-1���Σ���Ϊÿ������һ���ߣ��պ����ӡ�������-1������ 
	{
		j = MinEdge(shortEdge, MG.vertexNum);
		cout << "<" << shortEdge[j].adjvex << "," << j << ">" << shortEdge[j].lowcost << endl;
		shortEdge[j].lowcost = 0;
		for(int i=0;i<MG.vertexNum;i++)		
			if (MG.arc[i][j] < shortEdge[i].lowcost)	//��ʱshortEdge[i].lowcost����ʾ����һ�������
			{											//�����j��Сȡ����֮���ɣ�ά��shortEdge
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