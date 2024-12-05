#include<iostream>

using namespace std;


//������������Ϊ�գ���ý�������ָ����ǰ�����
//������������Ϊ�գ���ý����Һ���ָ�����̽��
//�����µ�ǰ���ͺ��
template<typename T>
struct ThreadNode
{
	T val;
	ThreadNode<T>* left, * right;
	bool ltag, rtag;  
	//0��ʾ����ָ����Ů��1��ʾָ��ǰ��(l)���(r)��������
	ThreadNode(const T item) :val(item), left(NULL), right(NULL), ltag(0), rtag(0) {}
};

template<typename T>
class ThreadTree
{
private:
	ThreadNode<T>* root;
	T RefValue;

private:
	//ǰ���������������(δ������)
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

	//�������������
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

	//Ѱ�������µ�һ�����
	ThreadNode<T>* First(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current;
		while (p->ltag == 0)
			p = p->left;
		return p;
	}

	//Ѱ�Һ�̽��
	ThreadNode<T>* Next(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current->right;
		if (current->ratg == 0) return First(p);
		else return p;
	}

	//Ѱ�����һ�����
	ThreadNode<T>* Last(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current;
		while (p->rtag == 0)
			p = p->right;
		return p;
	}

	//Ѱ��ǰ�����
	ThreadNode<T>* Prior(ThreadNode<T>* current)
	{
		ThreadNode<T>* p = current->left;
		if (current->ltag == 0) return Last(p);
		else return p;
	}

	//Ѱ�Ҹ��ڵ�
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

	//�������
	void InOrder(ThreadNode<T>* p)
	{
		for (p = First(root); p != NULL; p = Next(p))
			cout << p->val << " ";
		cout << endl;
	}

	//ǰ�����
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

	//�������

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