#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int part(vector<int>& a, int low, int high)
{
	int i = low, j = high, pivot = a[low];
	//pivot为基准元素，小的在其左边
	while (i < j)
	{
		while (i<j && a[j]>pivot)
			j--;
		if (i < j)
			swap(a[i++], a[j]);
		while (i < j && a[i] <= pivot)
			i++;
		if (i < j)
			swap(a[i], a[j--]);
	}
	return i;
}

void quick_sort(vector<int>& a,int low,int high)
{
	int n = a.size();
	int mid;
	if (low < high)
	{
		mid = part(a, low, high);
		quick_sort(a, low, mid - 1);
		quick_sort(a, mid+1, high);
	}
}

int main()
{
	vector<int> a{ 9,6,8,3,1 };
	for (int x : a)
		cout << x;
	cout << endl;
	quick_sort(a, 0, 4);
	for (int x : a)
		cout << x;
	cout << endl;
	return 0;
}