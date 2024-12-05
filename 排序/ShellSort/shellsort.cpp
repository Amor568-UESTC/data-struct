#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void shell_sort(vector<int>& a)
{
	int i, j, gap, n = a.size();
	for (gap = n / 2; gap > 0; gap /= 2) 
		for (i = 0; i < gap; i++) 
			for (j = i + gap; j < n; j += gap) 
				// ���a[j] < a[j-gap]����Ѱ��a[j]λ�ã������������ݵ�λ�ö�����
				if (a[j] < a[j - gap])
				{
					int tmp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > tmp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = tmp;
				}
}


int main()
{
	vector<int> g = { 8,3,6,4,2,1,5,7 };
	shell_sort(g);
	for (int x : g)
		cout << x << ' ';
	cout << endl;
	return 0;
}