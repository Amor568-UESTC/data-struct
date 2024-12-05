#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

const int inf = 9999;

//����ͼ
class Graph
{
private:
	vector<vector<int>> arcs; //�ڽӾ���,���Ϊi��j����С·��ֵ
	vector<vector<int>> path; //��С·�������i��j·������i��ʼҪȥ����һ����
	int vexnum, arcnum;
public:
	void Create();
	void Floyd();
	void print_path();
	void Show();
};

//��ʼ��Graph
void Graph::Create()
{
	cout << "enter num of vertexes and arcs: ";
	cin >> vexnum >> arcnum;
	arcs.resize(vexnum, vector<int>(vexnum,inf));
	for (int i = 0; i < arcnum; i++)
	{
		int v1, v2, w;
		cout << "pleas enter the " << i << " arc's start,end and weight";
		cin >> v1 >> v2 >> w;
		arcs[v1][v2] = w;
	}
	path.resize(vexnum, vector<int>(vexnum));
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			path[i][j] = j;
}

void Graph::Show()
{
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
			cout << setw(4) << arcs[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

void Graph::Floyd()
{
	for (int k = 0; k < vexnum; k++)
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				if (arcs[i][k] + arcs[k][j] < arcs[i][j])
				{
					arcs[i][j] = arcs[i][k] + arcs[k][j];
					path[i][j] = path[i][k];
					//��¼i��j��һ��Ҫȥ�ĵ�,�����Ϊk
				}
	for (int i = 0; i < vexnum; i++)
		arcs[i][i] = 0;					
}

void Graph::print_path()
{
	cout << "vertexes' shortest road: " << endl;
	int r = 0, c = 0, tmp = 0;
	for(r=0;r<vexnum;r++)
		for(c=r+1;c<vexnum;c++)
			if (arcs[r][c] != inf)
			{
				cout << "v" << to_string(r) << "--->" << "v" << to_string(c) << "weihgt: "
					<< arcs[r][c] << " path: " << "v" << to_string(r);
				tmp = path[r][c]; //��һ��Ҫȥ�Ķ���
				while (tmp != c)
				{
					cout << "--->" << "v" << to_string(tmp);
					tmp = path[tmp][c]; //������tmp����
				}
				cout << "--->" << "v" << to_string(c) << endl;
			}
	cout << endl;
}



int main()
{
	Graph s;
	s.Create();
	s.Show();
	s.Floyd();
	s.print_path();
	system("pause");
	return 0;
}
