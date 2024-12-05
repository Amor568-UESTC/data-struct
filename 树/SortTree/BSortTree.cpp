/*
���������������������������������н�����������ֵ��С�ڸýڵ��ֵ����������ֵ�����ڸýڵ��ֵ
https://blog.csdn.net/kang___xi/article/details/80392565
*/
#include<iostream>
#include<queue>
using namespace std;
typedef int ElemType;
typedef int KeyType;
typedef struct BSTNode {
	KeyType key;
	ElemType data;
	BSTNode* left, * right;
	BSTNode() = default;
	BSTNode(KeyType k) :key(k), data(0), left(NULL), right(NULL) {}
}BSTree;

BSTree* SearchBST(BSTree* rt, KeyType k) {		//����
	if (rt == NULL || k == rt->key)	return rt;
	if (k < rt->key)	return SearchBST(rt->left, k);
	else	return SearchBST(rt->right, k);
}

bool InsertBST(BSTree*& rt, KeyType k) {		//����
	if (rt == NULL) {
		rt = new BSTNode(k);
		return true;
	}
	if (k == rt->key)	return false;
	if (k < rt->key)	return InsertBST(rt->left, k);
	else	return InsertBST(rt->right, k);
}


void DeleteBST_(BSTree*& rt, BSTree* pt) {	//ɾ���ڵ�����������ʱ����
	if (rt->right == NULL) {
		BSTNode* p = rt;
		pt->key = rt->key;
		pt->data = rt->data;
		rt = rt->left;
		delete p;
	}
	else {
		DeleteBST_(rt->right, pt);
	}
}

/*
ɾ���ڵ㣬���������
һ����ɾ���ڵ�û�к��ӽڵ㣬��ֱ��ɾ������
������ɾ���ڵ�ֻ��һ�����ӽڵ㣬���亢�ӽڵ����ɾ���ڵ��λ�ã����ɾ���ڵ㼴��
������ɾ���ڵ������Һ��ӣ�����ƻ���ľ����ȡ�����������ֵ��Ҳ��ȡ����������Сֵ������ڱ�ɾ���ڵ��У����ɾ�������������ֵ�Ľڵ㼴��
�������һ����ͬ���������
*/
bool DeleteBST(BSTree*& rt, KeyType k) {		//ɾ��
	if (rt == NULL)	return false;
	int res = true;
	if (rt->key == k) {
		if (rt->left == NULL) {
			rt = rt->right;
		}
		else if (rt->right == NULL) {
			rt = rt->left;
		}
		else {
			DeleteBST_(rt->left, rt);
		}
	}
	else if (k < rt->key) {
		res = DeleteBST(rt->left, k);
	}
	else {
		res = DeleteBST(rt->right, k);
	}
	return res;
}

void InorderTraversal(BSTree* rt) {	//������� 
	if (rt == NULL)	return;
	InorderTraversal(rt->left);
	cout << rt->key << " ";
	InorderTraversal(rt->right);
}

void LevelOrder(BSTree* root) {	//������� 
	if (root == NULL)  return;
	queue<BSTree*> que;
	que.push(root);
	int n;
	BSTree* rt;
	cout << "�����������ǰ�ڵ� = ��ڵ� �ҽڵ�" << endl;
	while (!que.empty()) {
		n = que.size();
		while (n--) {
			rt = que.front();	que.pop();
			cout << rt->key << "\t=\t";
			if (rt->left)	cout << rt->left->key << "\t";
			else cout << "#\t";
			if (rt->right)	cout << rt->right->key << "\t";
			else cout << "#\t";
			cout << endl;
			if (rt->left)	que.push(rt->left);
			if (rt->right)	que.push(rt->right);
		}
	}
}

int main()
{
	int n = 10;
	int a[100] = { 4,2,6,9,7,1,5,8,10,3 };
	cout << "����˳��";
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
	BSTree* rt = NULL;
	for (int i = 0; i < n; ++i)
		InsertBST(rt, a[i]);
	cout << "���������";
	InorderTraversal(rt);
	cout << endl;
	cout << "#############################" << endl;
	LevelOrder(rt);
	cout << "#############################" << endl;
	for (int i = 0; i < n; ++i)
	{
		DeleteBST(rt, a[i]);
		cout << "ɾ�� " << a[i] << ": ";
		InorderTraversal(rt);
		cout << endl;
	}

	return 0;
}
