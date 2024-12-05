#include<iostream>
#include<string>
#include<iomanip>
#include<stack>
#include<algorithm>

using namespace std;

struct HFT
{
	float weight;
	int parent, LTree, RTree;
	string name;
};

void Select(HFT* &H, const int& n, int& s1, int& s2)	//找出两个最小权值的结点
{
	for (int i = 1; i < n; i++)
		if (H[i].parent == 0)
		{
			s1 = i;
			break;
		}
	//找到第一个暂无父母的结点
	for (int i = 1; i < n; i++) //因为第2n-1个元素parent为0
		if (H[i].parent == 0 && H[s1].weight > H[i].weight)
			s1 = i;

	for (int i = 1; i < n; i++)
		if (H[i].parent == 0 && i != s1)
		{
			s2 = i;
			break;
		}
	for (int i = 1; i < n; i++)
		if (H[i].parent == 0 && H[s2].weight > H[i].weight && i != s1)
			s2 = i;
}

void initHFT(HFT*& H, const int& n)
{
	if (n <= 1) return;
	int m = 2 * n - 1; //数组共m个元素
	H = new HFT[m + 1]; //0号单元未存储
	for (int i = 1; i <= m; i++)
	{
		H[i].parent = H[i].LTree = H[i].RTree = 0;
		H[i].name = "no name";
	}
		
	cout << "please input the weight of nodes and nodes' name:" << endl;
	for (int i = 1; i <= n; i++)
		cin >> H[i].weight >> H[i].name;
	cout << endl;
	for (int i = n + 1; i <= m; i++)
	{
		int s1, s2;
		Select(H, i, s1, s2);
		H[s1].parent = H[s2].parent = i;
		H[i].LTree = s1;
		H[i].RTree = s2;
		H[i].weight = H[s1].weight + H[s2].weight;
	}
}

void CreateHFMcode(HFT*& H, string* HC, const int& n)
{
	string tmp;
	stack<string> st;
	int cur = 0, father = 0;
	//对叶子结点上溯编码
	for (int i = 1; i <= n; i++)
	{
		cur = i;
		father = H[i].parent;
		while (father != 0)
		{
			if (H[father].LTree == cur) st.push("0"); //左子树0
			else st.push("1");
			cur = father;
			father = H[father].parent;
		}
		while (!st.empty())
		{
			tmp += st.top();
			st.pop();
		}
		HC[i] = tmp;
		tmp = ""; 
	}
}

void showdata(HFT*& H, string* HC, const int& n)
{
	cout << "index  weight  parent  LTree  RTree" << endl;
	cout << left;
	int m = 2 * n - 1;
	for (int i = 1; i <= m; i++)
	{
		cout << setw(5) << i << "  ";
		cout << setw(6) << H[i].weight << "  ";
		cout << setw(6) << H[i].parent << "  ";
		cout << setw(6) << H[i].LTree << "  ";
		cout << setw(6) << H[i].RTree << "  " << endl;
	}
	cout << endl;

	cout << "Name HFMCode" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << setw(5) << H[i].name << "  ";
		cout << setw(7) << HC[i] << "  " << endl;
	}
}

int main()
{
	HFT* H;
	int n = 0;
	cout << "please input the num of verctices:";
	cin >> n;
	string* HC = new string[n];
	initHFT(H, n);
	CreateHFMcode(H, HC, n);
	showdata(H, HC, n);
	return 0;
}