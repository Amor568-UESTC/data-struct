#include <iostream>
using namespace std;

template <typename T>
struct AVLTreeNode
{
    T m_key;                  // �ؼ���
    int m_height;             // �߶�
    AVLTreeNode* m_leftChild; // ����
    AVLTreeNode* m_rightNode; // �Һ���
    AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r) : m_key(value), m_height(0), m_leftChild(l), m_rightNode(r) {}
};

template <typename T>
class AVLTree
{
public:
    AVLTree() : m_root(NULL) {}
    ~AVLTree() { destroy(m_root); }

public:
    // �������
    void inOrder() { inOrder(m_root); }

    // �������
    void preOrder() { preOrder(m_root); }

    // ���ĸ߶�
    int height() { return height(m_root); }

    // ����AVL����ֵΪkey�Ľ�㣨�ݹ飩
    AVLTreeNode<T>* search(T key) { return search(m_root, key); }

    // ����AVL����ֵΪkey�Ľ�㣨�ǵݹ飩
    AVLTreeNode<T>* iterativeSearch(T key) { return iterativeSearch(m_root, key); }

    // ������С��㣬������С���ļ�ֵ
    T minimum()
    {
        AVLTreeNode<T>* p = minimum(m_root);
        if (p != NULL)
            return p->m_key;
        return (T)NULL;
    }

    // ��������㣬���������ļ�ֵ
    T maximum()
    {
        AVLTreeNode<T>* p = maximum(m_root);
        if (p != NULL)
            return p->m_key;
        return (T)NULL;
    }

    // ����ֵΪkey�Ľ����뵽AVL��
    void insert(T key) { insert(m_root, key); }

    // ɾ����ֵΪkey�Ľ��
    void remove(T key)
    {
        AVLTreeNode<T>* z = search(m_root, key);
        if (z != NULL)
            m_root = remove(m_root, z);
    }

    // ����AVL��
    void destroy() { destroy(m_root); }

private:
    void inOrder(AVLTreeNode<T>* node)
    {
        if (node == NULL)
            return;
        inOrder(node->m_leftChild);
        cout << node->m_key << " ";
        inOrder(node->m_rightNode);
    }

    void preOrder(AVLTreeNode<T>* node)
    {
        if (node == NULL)
            return;
        cout << node->m_key << " ";
        preOrder(node->m_leftChild);
        preOrder(node->m_rightNode);
    }

    int height(AVLTreeNode<T>* node)
    {
        return node != NULL ? node->m_height : 0;
    }

    void destroy(AVLTreeNode<T>*& tree)
    {
        if (tree == NULL)
            return;
        if (tree->m_leftChild != NULL)
            destroy(tree->m_leftChild);
        if (tree->m_rightNode != NULL)
            destroy(tree->m_rightNode);
        delete tree;
    }

    AVLTreeNode<T>* search(AVLTreeNode<T>* node, T key)
    {
        if (node == NULL || node->m_key == key)
            return node;
        if (key < node->m_key)
            return search(node->m_leftChild, key);
        else
            return search(node->m_rightNode, key);
    }

    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* node, T key)
    {
        while ((node != NULL) && (node->m_key != key))
        {
            if (key < node->m_key)
                node = node->m_leftChild;
            else
                node = node->m_rightNode;
        }
        return node;
    }

    AVLTreeNode<T>* minimum(AVLTreeNode<T>* node)
    {
        if (node == NULL)
            return NULL;
        while (node->m_leftChild != NULL)
        {
            node = node->m_leftChild;
        }
        return node;
    }

    AVLTreeNode<T>* maximum(AVLTreeNode<T>* node)
    {
        if (node == NULL)
            return NULL;
        while (node->m_rightNode != NULL)
        {
            node = node->m_rightNode;
        }
        return node;
    }

    AVLTreeNode<T>* insert(AVLTreeNode<T>*& node, T key)
    {
        if (node == NULL)
        {
            node = new AVLTreeNode<T>(key, NULL, NULL);
        }
        else if (key < node->m_key) // key����node�������������
        {
            node->m_leftChild = insert(node->m_leftChild, key);
            // ����ڵ�����AVL��ʧ�⣬��Ҫ������Ӧ����
            if (height(node->m_leftChild) - height(node->m_rightNode) == 2)
            {
                if (key < node->m_leftChild->m_key)
                    node = leftLeftRotation(node);
                else
                    node = leftRightRotation(node);
            }
        }
        else if (key > node->m_key) // key����node�������������
        {
            node->m_rightNode = insert(node->m_rightNode, key);
            // ����ڵ�����AVL��ʧ�⣬��Ҫ������Ӧ����
            if (height(node->m_rightNode) - height(node->m_leftChild) == 2)
            {
                if (key > node->m_rightNode->m_key)
                    node = rightRightRotation(node);
                else
                    node = rightLeftRotation(node);
            }
        }
        else
        {
            cout << "���ʧ�ܣ����������ͬ�Ľ��" << endl;
        }
        node->m_height = max(height(node->m_leftChild), height(node->m_rightNode)) + 1;
        return node;
    }

    AVLTreeNode<T>* remove(AVLTreeNode<T>*& node, AVLTreeNode<T>* z)
    {
        if (node == NULL || z == NULL)
            return NULL;

        if (z->m_key < node->m_key) // ��ɾ���Ľڵ���tree����������
        {
            node->m_leftChild = remove(node->m_leftChild, z);
            // ɾ���ڵ�����AVL��ʧ�⣬��Ҫ������Ӧ����
            if (height(node->m_rightNode) - height(node->m_leftChild) == 2)
            {
                AVLTreeNode<T>* r = node->m_rightNode;
                if (height(r->m_leftChild) > height(r->m_rightNode))
                    node = rightLeftRotation(node);
                else
                    node = rightRightRotation(node);
            }
        }
        else if (z->m_key > node->m_key) //��ɾ���Ľڵ���node����������
        {
            // ɾ���ڵ�����AVL��ʧ�⣬��Ҫ������Ӧ����
            node->m_rightNode = remove(node->m_rightNode, z);
            if (height(node->m_leftChild) - height(node->m_rightNode) == 2)
            {
                AVLTreeNode<T>* l = node->m_leftChild;
                if (height(l->m_rightNode) > height(l->m_leftChild))
                    node = leftRightRotation(node);
                else
                    node = leftLeftRotation(node);
            }
        }
        else //��ǰnode����Ҫɾ���Ľڵ�
        {
            if ((node->m_leftChild != NULL) && (node->m_rightNode != NULL))
            {
                if (height(node->m_leftChild) > height(node->m_rightNode))
                {
                    if (height(node->m_leftChild) > height(node->m_rightNode))
                    {
                        /* ���node�ڵ�����������������ߣ���:
                         * (01)�ҳ�node�������������ڵ�
                         * (02)�������ڵ��ֵ��ֵ��node
                         * (03)ɾ�������ڵ�
                         * �൱����node�������������ڵ���Ϊnode������
                         * ���ַ�ʽɾ��node�����������ڵ�֮��AVL����Ȼ��ƽ���
                         */
                        AVLTreeNode<T>* max = maximum(node->m_leftChild);
                        node->m_key = max->m_key;
                        node->m_leftChild = remove(node->m_leftChild, max);
                    }
                    else
                    {
                        /* ���node�ڵ�����������������ߣ���:
                         * (01)�ҳ�node������������С�ڵ�
                         * (02)������С�ڵ��ֵ��ֵ��node
                         * (03)ɾ������С�ڵ�
                         * �൱����node������������С�ڵ���Ϊnode������
                         * ���ַ�ʽɾ��node����������С�ڵ�֮��AVL����Ȼ��ƽ���
                         */
                        AVLTreeNode<T>* min = minimum(node->m_rightNode);
                        node->m_key = min->m_key;
                        node->m_rightNode = remove(node->m_rightNode, min);
                    }
                }
            }
            else
            {
                // ��ɾ���Ľڵ����node������node��һ������
                // ����ǰ�ڵ�ָ��ú��ӽڵ㲢ɾ����ǰ�ڵ�
                AVLTreeNode<T>* tmp = node;
                node = node->m_leftChild != NULL ? node->m_leftChild : node->m_rightNode;
                delete tmp;
            }
        }
        return node;
    }

private:
    /* LL�������������ʧȥƽ��(����ת)
     *       k2              k1
     *      /  \            /  \
     *     k1   z   ===>   x    k2
     *    /  \                 /  \
     *   x    y               y    z
     */

    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>*& k2)
    {
        AVLTreeNode<T>* k1 = k2->m_leftChild;
        k2->m_leftChild = k1->m_rightNode;
        k1->m_rightNode = k2;
        k2->m_height = std::max(height(k2->m_leftChild), height(k2->m_rightNode)) + 1;
        k1->m_height = std::max(height(k1->m_leftChild), k2->m_height) + 1;
        return k1;
    }

    /* RR�����������ұ�ʧȥƽ��(�ҵ���ת)
     *       k1              k2
     *      /  \            /  \
     *     x   k2   ===>   k1   z
     *        /  \        /  \
     *       y    z      x    y
     */
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>*& k1)
    {
        AVLTreeNode<T>* k2 = k1->m_rightNode;
        k1->m_rightNode = k2->m_leftChild;
        k2->m_leftChild = k1;

        k1->m_height = std::max(height(k1->m_leftChild), height(k1->m_rightNode)) + 1;
        k2->m_height = std::max(height(k2->m_rightNode), k1->m_height) + 1;
        return k2;
    }

    /* LR�����������ұ�ʧȥƽ��(��˫��ת)
     *       k3               k3               k2
     *      /  \     RR      /  \     LL      /  \
     *     k1   D   ===>   k2    D   ===>   k1    k3
     *    /  \            /  \             /  \  /  \
     *   A    K2         k1   C           A    B C   D
     *       /  \       /  \
     *      B    C     A    B
     */
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>*& k3)
    {
        k3->m_leftChild = rightRightRotation(k3->m_leftChild);
        return leftLeftRotation(k3);
    }

    /* RL�������������ʧȥƽ��(��˫��ת)
     *     k1               k1                K2
     *    /  \      LL     /  \      RR      /  \
     *   A    k3   ===>   A    k2   ===>   k1    K3
     *       /  \             /  \        /  \  /  \
     *      k2   D           B    k3     A    B C   D
     *     /  \                  /   \
     *    B    D                C     D
     */
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>*& k1)
    {
        k1->m_rightNode = leftLeftRotation(k1->m_rightNode);
        return rightRightRotation(k1);
    }

private:
    AVLTreeNode<T>* m_root; // AVL���ĸ��ڵ�
};

int main()
{
    AVLTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    tree.insert(16);
    tree.insert(15);
    tree.insert(14);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(10);
    tree.insert(8);
    tree.insert(9);

    tree.preOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;

    tree.remove(8);
    tree.preOrder();
    cout << endl;
    tree.preOrder();
    cout << endl;

    return 0;
}
