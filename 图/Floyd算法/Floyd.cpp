#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

const int inf = 9999;

//有向图
class Graph
{
private:
	vector<vector<int>> arcs; //邻接矩阵,后变为i到j的最小路径值
	vector<vector<int>> path; //最小路径保存从i到j路径，从i开始要去的下一个点
	int vexnum, arcnum;
public:
	void Create();
	void Floyd();
	void print_path();
	void Show();
};

//初始化Graph
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
					//记录i到j第一个要去的点,这里变为k
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
				tmp = path[r][c]; //第一个要去的顶点
				while (tmp != c)
				{
					cout << "--->" << "v" << to_string(tmp);
					tmp = path[tmp][c]; //继续从tmp出发
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
