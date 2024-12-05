#include<iostream>
#include<string>

using namespace std;

//s2Ϊ�Ӵ�,next��Ҫ�ص����±�
void GetNext(const string& s2, int* next)
{
	int i = 0;
	int k = -1;
	int len = s2.length();
	next[0] = -1;
	while (i < len)
	{
		if (k == -1 || s2[i] == s2[k])
		{
			k++;
			i++;
			next[i] = k;
			//�������ɵ��ƹ�ϵ�õ���
		}
		else k = next[k];
		//�ַ���ͬ�����
	}
}

int KMP(const string& s1, const string& s2)
{
	int len1 = s1.length();
	int len2 = s2.length();
	if (len2<0 || len2>len1) return -1;
	if (len1 == 0 || len2 == 0) return -1;
	int* next = new int[len2];
	GetNext(s2, next);
	int i = 0, j = 0;
	while (j == -1 || i < len1 && j < len2)
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else j = next[j];
	}
	if (j >= len2) return i - j;
	//�����������ִ�ƥ�䵽�ɹ��Ŀ�ʼλ��
	return -1;
}

int main()
{
	string s1 = "abababcabc";
	string s2 = "abcabc";
	cout << KMP(s1, s2);
	return 0;
}