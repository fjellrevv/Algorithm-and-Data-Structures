#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
using namespace std;
#define SIZE 100000
const double PI = 3.141592653589793;

// ���������� ������
class Node {
public:
	double data;
	Node* prev, * next;
public:
	Node(double data) {
		this->data = data;
		this->prev = this->next = NULL;
	}
};
class LinkedList {
public:
	Node* head, * tail;

public:
	LinkedList() {
		head = tail = NULL;
	}

	~LinkedList() {
		while (head != NULL) pop_front();
	}

	Node* push_front(double data) {
		Node* ptr = new Node(data);
		ptr->next = head;
		if (head != NULL) head->prev = ptr;
		if (tail == NULL) tail = ptr;
		head = ptr;

		return ptr;
	}

	Node* push_back(double data) {
		Node* ptr = new Node(data);
		ptr->prev = head;
		if (tail != NULL) tail->next = ptr;
		if (head == NULL) head = ptr;
		tail = ptr;

		return ptr;
	}

	void pop_front() {
		if (head == NULL) return;

		Node* ptr = head->next;
		if (ptr != NULL) ptr->prev = NULL;
		else tail = NULL;

		delete head;
		head = ptr;
	}

	void pop_back() {
		if (tail == NULL) return;

		Node* ptr = tail->prev;
		if (ptr != NULL) ptr->next = NULL;
		else head = NULL;

		delete tail;
		tail = ptr;
	}

	Node* getAt(int index) {
		Node* ptr = head;
		int n = 0;

		while (n != index) {
			if (ptr == NULL) return ptr;
			ptr = ptr->next;
			n++;
		}

		return ptr;
	}

	Node* insert(int index, double data) {
		Node* right = getAt(index);
		if (right == NULL) return push_back(data);

		Node* left = right->prev;
		if (left == NULL) return push_front(data);

		Node* ptr = new Node(data);

		ptr->prev = left;
		ptr->next;
		left->next = ptr;
		right->prev = ptr;

		return ptr;
	}

	void erase(int index) {
		Node* ptr = getAt(index);
		if (ptr == NULL) return;

		if (ptr->prev == NULL) {
			pop_front();
			return;
		}

		if (ptr->next == NULL) {
			pop_back();
			return;
		}

		Node* left = ptr->prev;
		Node* right = ptr->next;
		left->next = right;
		right->prev = left;

		delete ptr;
	}
};

// ������������ ������
class DynamicArr
{
private:
	int num;
	double* arr = new double[SIZE];
public:
	void input(int num)
	{
		for (int i = 0; i < num; i++) 
		{
			cin >> arr[i];
		}
	}
	void push(double x, int addr)
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
	void output()
	{
		for (int i = 0; i < num; i++)
			cout << arr[i] << " " << endl;
	}
	void get_int() 
	{
		cin >> num;
	}
	~DynamicArr();
};
DynamicArr::~DynamicArr() 
{
	delete[] arr;
}

// ����
class Stack
{
	string* arr;
	int top;
	int capacity;

public:
	Stack(int size = SIZE) 
	{
		arr = new string[size];
		capacity = size;
		top = -1;
	}
	~Stack() 
	{
		if (top != -1) delete[] arr;
	}

	void push(string x)
	{
		if (isFull())
		{
			cout << "������������ �����!\n\n";
		}
		else arr[++top] = x;
	}
	string pop()
	{
		if (isEmpty())
		{
			return 0;
		}
		return arr[top--];
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
		return top == capacity - 1;     // ��� return size() == capacity;
	}
};

// �������� ������������� �������
double algo(Stack num, Stack oper, string* token, int size)
{
	double ans = 0;
	for (int i = 0; i < size; i++)
	{
		if (token[i] == "(" || token[i] == "s" || token[i] == "c") oper.push(token[i]);
		else if (token[i] == "^")
		{
			oper.push(token[i]);
		}
		else if (token[i] == ")")
		{
			while (oper.peek() != "(")
			{
				// ��������
				double b = stod(num.peek().c_str()); num.pop();
				double a = stod(num.peek().c_str()); num.pop();

					if (oper.peek() == "*") ans = a * b;
					else if (oper.peek() == "/") ans = a / b;
					else if (oper.peek() == "+") ans = a + b;
					else if (oper.peek() == "-") ans = a - b;
					else if (oper.peek() == "^") ans = pow(a, b);

				string num_str = to_string(ans);
				num.push(num_str);
				oper.pop();
			}
			oper.pop();
			if (oper.peek() == "s")
			{
				double b = stod(num.peek().c_str()); num.pop();
				ans = sin(b);
				string num_str = to_string(ans);
				num.push(num_str);
				oper.pop();
			}
			else if (oper.peek() == "c")
			{
				double b = stod(num.peek().c_str()); num.pop();
				ans = cos(b);
				string num_str = to_string(ans);
				num.push(num_str);
				oper.pop();
			}
		}
		// �������� � ���������
		else if (token[i] == "+" || token[i] == "-")
		{
			if (oper.isEmpty() || oper.peek() == "(")
			{
				oper.push(token[i]);
			}
			else
			{
				while (oper.peek() != "(" && !oper.isEmpty())
				{
					// ��������
					double b = stod(num.peek().c_str()); num.pop();
					double a = stod(num.peek().c_str()); num.pop();

					if (oper.peek() == "*") ans = a * b;
					else if (oper.peek() == "/") ans = a / b;
					else if (oper.peek() == "+") ans = a + b;
					else if (oper.peek() == "-") ans = a - b;
					else if (oper.peek() == "^") ans = pow(a, b);

					string num_str = to_string(ans);
					num.push(num_str);
					oper.pop();
				}
				oper.push(token[i]);
			}
		}
		// ��������� � �������
		else if (token[i] == "*" || token[i] == "/")
		{
			if (oper.isEmpty() || (oper.peek() != "^" && oper.peek() != "*" && oper.peek() != "/"))
			{
				oper.push(token[i]);
				continue;
			}
			while (!oper.isEmpty() && (oper.peek() != "(" && oper.peek() != "+" && oper.peek() != "-"))
			{
				// ��������
				double b = stod(num.peek().c_str()); num.pop();
				double a = stod(num.peek().c_str()); num.pop();

				if (oper.peek() == "*") ans = a * b;
				else if (oper.peek() == "/") ans = a / b;
				else if (oper.peek() == "^") ans = pow(a, b);

				string num_str = to_string(ans);
				num.push(num_str);
				oper.pop();
			}
			oper.push(token[i]);
		}
		// �����
		else
		{
			if (token[i] == "p") num.push(to_string(PI));
			else num.push(token[i]);

			// ��������� ����� - �����
			if (i == size - 1)
			{
				while (!oper.isEmpty())
				{
					// ��������
					double b = stod(num.peek().c_str()); num.pop();
					double a = stod(num.peek().c_str()); num.pop();

					if (oper.peek() == "*") ans = a * b;
					else if (oper.peek() == "/") ans = a / b;
					else if (oper.peek() == "+") ans = a + b;
					else if (oper.peek() == "-") ans = a - b;
					else if (oper.peek() == "^") ans = pow(a, b);

					string num_str = to_string(ans);
					num.push(num_str);
					oper.pop();
				}
			}
		}
	}
	while (!oper.isEmpty())
	{
		if (oper.peek() == "s")
		{
			double b = stod(num.peek().c_str()); num.pop();
			ans = sin(b);
			string num_str = to_string(ans);
			num.push(num_str);
			oper.pop();
		}
		else if (oper.peek() == "c")
		{
			double b = stod(num.peek().c_str()); num.pop();
			ans = cos(b);
			string num_str = to_string(ans);
			num.push(num_str);
			oper.pop();
		}
		else 
		{
			double b = stod(num.peek().c_str()); num.pop();
			double a = stod(num.peek().c_str()); num.pop();

			if (oper.peek() == "*") ans = a * b;
			else if (oper.peek() == "/") ans = a / b;
			else if (oper.peek() == "+") ans = a + b;
			else if (oper.peek() == "-") ans = a - b;
			else if (oper.peek() == "^") ans = pow(a, b);

			string num_str = to_string(ans);
			num.push(num_str);
			oper.pop();
		}
	}
	return stod(num.peek().c_str());
}

string* Token(string math, string* token, int &size_t, bool &flag)
{
	string temp = ""; int cnt_1 = 0;
	int i = 0; size_t = -1;
	while (i < math.size()) {
		switch (math[i])
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case 'p':
			temp += math[i];
ъээээ
			if (i > 0) if (math[i - 1] == '/' && math[i] == '0') flag = 0;

			if (i == math.size() - 1) token[++size_t] = temp;
			i++; continue;
		case '+': case '-': case '*': case '/': case '^': case '(': case ')':
			if (math[i] == '(')
			{
				cnt_1++;
			}
			if (math[i] == ')')
			{
				cnt_1--;
				if (cnt_1 < 0) flag = 0;
			}
			if (temp != "") // �����
			{
				size_t++;
				token[size_t] = temp;
			} 
			token[++size_t] = math[i]; // ��������
			temp = "";
			i++; continue;
		case 's': case 'c':
			token[++size_t] = math[i];
			i += 3; continue;
		default:
			i++; continue;
		}
	}
	size_t++;
	if (cnt_1 != 0) flag = 0;
	return token;
}

int main() {

	setlocale(LC_ALL, "Rus");
	int choice = 0; string math; int size = -1; int* size_t = &size; bool flag = 1;
	string* token = new string[SIZE];
	while (1)
	{
		cout << "�����������\n\n��������� �������: +, -, *, /, ^, sin, cos, (, ), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9\n\n������� �������������� ���������: ";
		cin >> math;
		token = Token(math, token, *size_t, flag);
		if (flag == 0) cout << "\n\n������������ ������! ������� ��������� ��� ���: ";
		while (flag == 0)
		{
			cin >> math;
			flag = 1;
			token = Token(math, token, *size_t, flag);
			if (flag == 0) cout << "\n\n������������ ������! ������� ��������� ��� ���: ";
		}
		Stack num(size), oper(size);
		double ans = algo(num, oper, token, size);
		cout << "�����: " << ans << "\n\n������� 1 ��� ����������� ��� ����� ������ �������, ����� ����� �� ���������: ";
		cin >> choice;
		if (choice == 1)
		{
			system("cls");
			ans = 0; size = -1; choice = 0;
			for (int i = 0; i < size; i++) token[i] = "";
		}
		else break;
	}
	delete[] token;
	return 0;
}