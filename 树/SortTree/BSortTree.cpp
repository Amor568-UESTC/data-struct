/*
二叉排序树（二叉搜索树）：树上所有结点的左子树的值均小于该节点的值，右子树的值均大于该节点的值
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

BSTree* SearchBST(BSTree* rt, KeyType k) {		//查找
	if (rt == NULL || k == rt->key)	return rt;
	if (k < rt->key)	return SearchBST(rt->left, k);
	else	return SearchBST(rt->right, k);
}

bool InsertBST(BSTree*& rt, KeyType k) {		//插入
	if (rt == NULL) {
		rt = new BSTNode(k);
		return true;
	}
	if (k == rt->key)	return false;
	if (k < rt->key)	return InsertBST(rt->left, k);
	else	return InsertBST(rt->right, k);
}


void DeleteBST_(BSTree*& rt, BSTree* pt) {	//删除节点有左右子树时处理
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
删除节点，分三种情况
一：被删除节点没有孩子节点，则直接删除即可
二：被删除节点只有一个孩子节点，则将其孩子节点代替删除节点的位置，随后删除节点即可
三：被删除节点有左右孩子，则可移花接木，即取左子树的最大值（也可取右子树的最小值）存放在被删除节点中，随后删除左子树的最大值的节点即可
对于情况一，可同情况二处理
*/
bool DeleteBST(BSTree*& rt, KeyType k) {		//删除
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

void InorderTraversal(BSTree* rt) {	//中序遍历 
	if (rt == NULL)	return;
	InorderTraversal(rt->left);
	cout << rt->key << " ";
	InorderTraversal(rt->right);
}

void LevelOrder(BSTree* root) {	//层序遍历 
	if (root == NULL)  return;
	queue<BSTree*> que;
	que.push(root);
	int n;
	BSTree* rt;
	cout << "层序遍历：当前节点 = 左节点 右节点" << endl;
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
	cout << "插入顺序：";
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
	BSTree* rt = NULL;
	for (int i = 0; i < n; ++i)
		InsertBST(rt, a[i]);
	cout << "中序遍历：";
	InorderTraversal(rt);
	cout << endl;
	cout << "#############################" << endl;
	LevelOrder(rt);
	cout << "#############################" << endl;
	for (int i = 0; i < n; ++i)
	{
		DeleteBST(rt, a[i]);
		cout << "删除 " << a[i] << ": ";
		InorderTraversal(rt);
		cout << endl;
	}

	return 0;
}
