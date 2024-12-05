#include<iostream>

using namespace std;

template<typename T>
struct Node
{
	T val;
	Node* next;
	Node(const T item) :val(item), next(NULL) {}
};

template<typename T>
class List
{
private:
	Node* head;
	T end_value;

private:
	void CreateList(Node<T>*& l)
	{
		T item;
		if (cin >> item)
		{
			if (item != end_value)
			{
				l = new Node(item);
				if (l == NULL)
				{
					cout << "error!" << endl;
					exit(1);
				}
				CreateList(l->next);
			}
			else l = NULL;
		}
	}

public:
	List() :head(NULL) {}
	List(T value) :root(NULL), end_value(value) {}
	void CreateList() { CreateList(head); }
	void 
};