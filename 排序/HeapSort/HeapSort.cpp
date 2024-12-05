#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void maxheap_down(vector<int>& a,int start,int end)
{
	int c = start;
	int l = 2 * c + 1; //leftchild
	int tmp = a[c];
	for (; l <= end; c = l, l = 2 * l + 1)
	{
		if (l < end && a[l] < a[l + 1])
			l++;
		if (tmp >= a[l])
			break;
		else
		{
			a[c] = a[l];
			a[l] = tmp;
		}
	}
}

void heap_sort(vector<int>& a)
{
	int i;
	int n = a.size();
	for (i = n / 2 - 1; i >= 0; i--)
		maxheap_down(a, i, n - 1);
	for (i = n - 1; i > 0; i--)
	{
		swap(a[0], a[i]);
		maxheap_down(a, 0, i - 1);
	}
}

int main()
{
	vector<int> a = { 2,3,9,4,7,11,6,1,10,5,8 };
	for (int x : a)
		cout << x << ' ';
	cout << endl;
	heap_sort(a);
	for (int x : a)
		cout << x << ' ';
	cout << endl;
	return 0;
}