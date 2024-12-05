#include<iostream>

using namespace std;


//如果结点左子树为空，则该结点的左孩子指向其前驱结点
//如果结点右子树为空，则该结点的右孩子指向其后继结点
//中序下的前驱和后继
template<typename T>
struct ThreadNode
{
	T val;
	ThreadNode<T>* left, * right;
	bool ltag, rtag;  
	//0表示正常指向子女，1表示指向前驱(l)后继(r)，中序上
	ThreadNode(const T item) :val(item), left(NULL), right(NULL), ltag(0), rtag(0) {}
};

template<typename T>
class ThreadTree
{
private:
	ThreadNode<T>* root;
	T RefValue;

private:
	//前序遍历创建二叉树(未线索化)
	void CreateTree(ThreadNode<T> *&subTree)
	{
		T item;
		if (cin >> item)
		{
			if (item != RefValue)
			{
				subTree = new ThreadNode<T>(item);
				if (subTree == NULL)
				{
					cout << "error!" << endl;
					exit(1);
				}
				CreateTree(subTree->left);
				CreateTree(subTree->right);
			}
			else subTree = NULL;
		}
	}

	//中序遍历线索化
	void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre)
	{
		if (current == NULL) return;
		createInThread(current->left, pre);
		if (current->left == NULL)
		{
			current->left = pre;
			current->ltag = 1;
		}
		pre = current;
		createInThread(current->right, pre);
	}

	//寻找中序下第一个结点
	ThreadNode<T>* First(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current;
		while (p->ltag == 0)
			p = p->left;
		return p;
	}

	//寻找后继结点
	ThreadNode<T>* Next(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current->right;
		if (current->ratg == 0) return First(p);
		else return p;
	}

	//寻找最后一个结点
	ThreadNode<T>* Last(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current;
		while (p->rtag == 0)
			p = p->right;
		return p;
	}

	//寻找前驱结点
	ThreadNode<T>* Prior(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current->left;
		if (current->ltag == 0) return Last(p);
		else return p;
	}

	//寻找父节点
	ThreadNode<T>* Parent(ThreadNode<T>* t)
	{
		ThreadNode<T>* p;
		if (t == root) return NULL;
		for (p = t; p->ltag == 0; p = p->left)
			;
		if (p->left != NULL)
			for (p = p->left; p != NULL && p->left != t && p->right != t; p = p->right)
				;
		if (p = NULL || p->left == NULL)
		{
			for (p = t; p->rtag == 0; p = p->right)
				;
			for (p = p->right; p != NULL && p->left != t && p->right != t; p = p->left)
				;
		}
		return p;
	}

	//中序遍历
	void InOrder(ThreadNode<T>* p)
	{
		for (p = First(root); p != NULL; p = Next(p))
			cout << p->val << " ";
		cout << endl;
	}

	//前序遍历
	void PreOrder(ThreadNode<T>* p)
	{
		while (p != NULL)
		{
			cout << p->val << " ";
			if (p->ltag == 0)
				p = p->left;
			else if (p->rtag == 0)
				p = p->right;
			else
			{
				while (p != NULL && p->rtag == 1)
					p = p->right;
				if (p != NULL)
					p = p->right;
			}
		}
		cout << endl;
	}

	//后序遍历

public:
	ThreadTree() :root(NULL) {}
	ThreadTree(T value) :root(NULL), RefValue(value) {}
	void CreateTree() { CreateTree(root); }
	void CreateInThread()
	{
		ThreadNode<T>* pre = NULL;
		if (root != NULL)
		{
			createInThread(root, pre);
			pre->right = NULL;
			pre->rtag = 1;
		}
	}
	void InOrder() { InOrder(root); }
	void PreOrder() { PreOreder(root); }
};


int main()
{
	ThreadTree<char> tree('#');
	return 0;
}