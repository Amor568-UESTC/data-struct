#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

struct HFT
{
	int weight;
	int parent, LTree, RTree;
};

void Select(HFT* H, int n, int& s1, int& s2)	//�ҳ�������СȨֵ�Ľ��
{
	for (int i = 1; i < n; i++)
		if (H[i].parent == 0)
		{
			s1 = i;
			break;
		}
	//�ҵ���һ�����޸�ĸ�Ľ��
	for (int i = 1; i < n; i++) //��Ϊ��2n-1��Ԫ��parentΪ0
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
	int m = 2 * n - 1; //���鹲m��Ԫ��
	H = new HFT[m + 1]; //0�ŵ�Ԫδ�洢
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