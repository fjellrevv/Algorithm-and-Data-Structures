#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int SIZE = 100;

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int balance = 0;
};

class DynamicArr
{
private:
	int num;
public:
	int* arr = new int[SIZE];
	
	void input(int num)
	{
		for (int i = 0; i < num; i++)
		{
			cin >> arr[i];
		}
	}
	void push(int x, int addr)
	{
		if (addr > 0 && num != SIZE)
		{
			for (int i = num; i >= addr; i--)
			{
				arr[i] = arr[i - 1];
			}
			x = arr[addr];
		}
	}
	void del(int addr)
	{
		arr[addr] = NULL;
		if (addr > 0)
		{
			for (int i = addr; i <= num; i++)
			{
				arr[i] = arr[i + 1];
			}
		}
	}
	void output()
	{
		for (int i = 0; i < num; i++)
			cout << arr[i] << " " << endl;
	}
	void get_int()
	{
		cin >> num;
	}
	bool isEmpty()
	{
		for (int i = 0; i < SIZE; i++) if (arr[i] != NULL) return 1;
		return 0;
	}
	~DynamicArr();
};
DynamicArr::~DynamicArr()
{
	delete[] arr;
}

// Обход в ширину
void breadth_first_search(Node* root) {
	Node* list[SIZE], * list_n[SIZE];
	for (int i = 0; i < SIZE; i++) 
	{
		list[i] = NULL; list_n[i] = NULL;
	}
	list[0] = root;
	int size = 1;
	while (size != 0) 
	{
		int j = 0;
		for (int i = 0; i < size; i++) 
		{
			cout << list[i]->data << " ";
			if (list[i]->left != NULL) 
			{
				list_n[j] = list[i]->left; j++;
			}
			if (list[i]->right != NULL) 
			{
				list_n[j] = list[i]->right; j++;
			}
		}
		for (int i = 0; i < SIZE; i++) list[i] = list_n[i];
		size = 0;
		for (int i = 0; i < SIZE; i++)
		{
			if (list[i] == NULL) break;
			else size++;
		}
		for (int i = 0; i < SIZE; i++) list_n[i] = NULL;
	}
}

class Stack
{
	int capacity;

public:
	int top;
	string arr[SIZE];
	Stack(int size = SIZE)
	{
		string arr[SIZE];
		capacity = size;
		top = -1;
	}

	void push(string x)
	{
		if (isFull())
		{
			cout << "error!\n\n";
		}
		else arr[++top] = x;
	}
	string pop()
	{
		if (top - 1 >= -1)
		{
			arr[top] = "";
			return arr[top--];
		}
	}
	string peek()
	{
		if (!isEmpty()) {
			return arr[top];
		}
		return "";
	}
	int size()
	{
		return top + 1;
	}
	bool isEmpty()
	{
		return size() == 0;
	}
	bool isFull()
	{
		return top == capacity - 1;     
	}
};

void reverseStack(Stack* st, Stack* tmpStack)
{
	while (tmpStack->top != -1)
	{
		tmpStack->arr[tmpStack->top] = "";
		tmpStack->top--;
	}
	while (st->top != -1)
	{
		string item = st->peek();
		st->pop();
		tmpStack->push(item);
	}
	st = tmpStack;
}

struct Node *newNode(int data) {
	struct Node* Node = (struct Node*)malloc(sizeof(struct Node));
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;
	Node->parent = NULL;
	return (Node);
}

int Height(Node* root)
{
	if (root == NULL) return 0;
	int Left = Height(root->left), Right = Height(root->right);
	if (Left > Right) return Left + 1;
	else return Right + 1;
}

void SetBalance(Node* (&root))
{
	if (root != NULL) root->balance = Height(root->right) - Height(root->left);
}

void TurnRight(Node* (&root))
{
	Node* LeftSubtree, * LeftSubtreeRightSubtree;
	LeftSubtree = root->left;
	LeftSubtreeRightSubtree = LeftSubtree->right;
	LeftSubtree->right = root;
	root->left = LeftSubtreeRightSubtree;
	root = LeftSubtree;
	SetBalance(root->right);
	SetBalance(root);
}

void TurnLeft(Node* (&root))
{
	Node* RightSubtree, * RightSubtreeLeftSubtree;
	RightSubtree = root->right;
	RightSubtreeLeftSubtree = RightSubtree->left;
	RightSubtree->left = root;
	root->right = RightSubtreeLeftSubtree;
	root = RightSubtree;
	SetBalance(root->left);
	SetBalance(root);
}

void InsertAVL(Node* (&root), int data)
{
	if (root == NULL) {
		root = newNode(data);
	}
	else
	{
		if (data >= root->data)
		{
			InsertAVL(root->right, data);
			if (Height(root->right) - Height(root->left) > 1)
			{
				if (Height(root->right->right) < Height(root->right->left)) 
					TurnRight(root->right);
				TurnLeft(root);
			}
		}
		else if (data < root->data)
		{
			InsertAVL(root->left, data);
			if (Height(root->left) - Height(root->right) > 1)
			{
				if (Height(root->left->left) < Height(root->left->right))
					TurnLeft(root->left);
				TurnRight(root);
			}
		}
		SetBalance(root);
	}
}

// Прямой обход дерева	
void traversePreOrder(struct Node* temp, Stack* number_list) {
	if (temp != NULL) {
		cout << " " << temp->data;
		number_list->push(to_string(temp->data));
		traversePreOrder(temp->left, number_list);
		traversePreOrder(temp->right, number_list);
	}
}

// Центрированный обход дерева
void traverseInOrder(struct Node* temp) {
	if (temp != NULL) {
		traverseInOrder(temp->left);
		cout << " " << temp->data;
		traverseInOrder(temp->right);
	}
}

// Обратный обход дерева
void traversePostOrder(struct Node* temp) {
	if (temp != NULL) {
		traversePostOrder(temp->left);
		traversePostOrder(temp->right);
		cout << " " << temp->data;
	}
}

// Построение двоичного дерева
Node* Token(string tree_str, bool& flag, Node* root)
{
	Stack brackets{}, numbers{};
	string curr_number = ""; int curr_list = -1;
	int i = 0, size_t = -1, open_brackets = 0, close_brackets = 0;

	while (i < tree_str.size()) {

		switch (tree_str[i])
		{
		case '(': case ')':

			if (tree_str[i] == '(')
			{
				open_brackets++;
				brackets.push("(");
				i++; continue;
			}
			else if (tree_str[i] == ')')
			{
				close_brackets++;
				if (i == 0 || open_brackets < close_brackets)
				{
					flag = 0;
					return 0;
				}
				else {
					brackets.push(")");
					i++; continue;
				}
			}

		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			if (i == 0 || i == tree_str.size() - 1)
			{
				flag = 0;
				return 0;
			}
			else if (tree_str[i - 1] >= '0' && tree_str[i - 1] <= '9')
			{
				string temp = numbers.peek() + tree_str[i];
				numbers.pop();
				numbers.push(temp);
			}
			else
			{
				string temp = to_string(tree_str[i] - 48);
				numbers.push(temp);
			}
			i++; continue;

		default:
			flag = 0;
			return 0;
		}
	}
	if ((brackets.size()) / 2 != numbers.size())
	{
		flag = 0;
		return 0;
	}
	Stack tmpStack;
		reverseStack(&brackets, &tmpStack); 
		brackets = tmpStack;
		reverseStack(&numbers, &tmpStack);
		numbers = tmpStack;
		int cnt_br = 0;
		while (!(brackets.isEmpty()))
		{
			if (root == NULL)
			{
				root = newNode(stoi(numbers.peek()));
				numbers.pop(); brackets.pop();
				cnt_br++;
			}
			else
			{
				if (brackets.peek() == "(")
				{
					if ((root != NULL) && root->left == NULL && root->right == NULL && (cnt_br == 0))
					{
						flag = 0;
						return 0;
					}
					if (root->left == NULL)
					{
						cnt_br++;
						root->left = newNode(stoi(numbers.peek()));
						root->left->parent = root;
						root = root->left;
					}
					else if (root->right == NULL)
					{
						cnt_br++;
						root->right = newNode(stoi(numbers.peek()));
						root->right->parent = root;
						root = root->right;
					}
					else {
						flag = 0;
						return 0;
					}
					numbers.pop(); brackets.pop();
				}
				else
				{
					cnt_br--;
					if (root->parent != NULL) root = root->parent;
					brackets.pop();
				}
			}
		}
	while (root->parent != NULL) root = root->parent;
	return root;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string tree_string, number_string; bool flag = 1; Node* tree = NULL, * avl_tree = NULL;
	int n = 0; Stack number_list;
	while (1)
	{
		cout << "Введите правильную скобочную последовательность: ";
		cin >> tree_string;
		// формируем дерево
		tree = Token(tree_string, flag, tree);
		if (flag == 0)
		{
			system("cls");
			flag = 1;
			continue;
		}
		else break;
	}

	system("cls");
	cout << "Введённая скобочная последовательность: " << tree_string;
	cout << "\n\nОбход двоичного дерева в глубину (КЛП, прямой): "; 
	traversePreOrder(tree, &number_list);
	Stack tmpStack;
	reverseStack(&number_list, &tmpStack);
	number_list = tmpStack;
	while (number_list.size() != 0)
	{
		InsertAVL(avl_tree, stoi(number_list.peek()));
		number_list.pop();
	}
	cout << "\n\nОбход АВЛ дерева в ширину: "; breadth_first_search(avl_tree);
	cout << "\n\nОбход АВЛ дерева в глубину (ЛПК, обратный): "; traversePostOrder(avl_tree);
	cout << "\n\nОбход АВЛ дерева в глубину (ЛКП, центрированный): "; traverseInOrder(avl_tree);
	cout << "\n\nОбход АВЛ дерева в глубину (КЛП, прямой): "; traversePreOrder(avl_tree, &number_list); cout << endl;
	return 0;
}