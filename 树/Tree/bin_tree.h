#pragma once
#include<iostream>
using namespace std;

template<typename T>
struct TreeNode
{
	T val;
	TreeNode* left;
	TreeNode* right;
	
	TreeNode() :val(0), left(nullptr), right(nullptr) {}
	TreeNode(T x) :val(x), left(nullptr), left(nullptr) {}
	TreeNode(T x, TreeNode* l, TreeNode* r) :
		val(x), left(l), left(r) {}
};

//麻烦有点
template<typename T>
void CreateTreeNode(TreeNode<T>* tn)
{
	char c;
	cin >> c;
	if (c == '0')
	{
		tn = NULL;
		return;
	}
	else
	{
		tn = new TreeNode<T>;
		tn->val = c;
		CreateTreeNode(tn->left);
		CreateTreeNode(tn->right);
	}
}


template<class T>
class BiThrNode
{
	T val;
	BiThrNode* left, * right;
	int ltag, rtag;
	//0表示为孩子，1表示指向前驱后继的线索

	void createBiTree();
};


