#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

struct HFT
{
	int weight;
	int parent, LTree, RTree;
};

void Select(HFT* H, int n, int& s1, int& s2)	//找出两个最小权值的结点
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
		if (H[i].parent == 0 && H[s2].weight > H[i].weight && i!=s1)
			s2 = i;
}

void initHFT(HFT* &H, int n)
{
	if (n <= 1) return;
	int m = 2 * n - 1; //数组共m个元素
	H = new HFT[m + 1]; //0号单元未存储
	for (int i = 1; i <= m; i++)
		H[i].parent = H[i].LTree = H[i].RTree = 0;
	cout << "please input the weight of nodes:" << endl;
	for (int i = 1; i <= n; i++)
		cin >> H[i].weight;
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

void showHFT(HFT* &H, int n)
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
}

int main()
{
	HFT* H;
	int n = 0;
	cout << "please input the num of nodes: ";
	cin >> n;
	initHFT(H, n);
	showHFT(H, n);
	system("pause");
	return 0;
}