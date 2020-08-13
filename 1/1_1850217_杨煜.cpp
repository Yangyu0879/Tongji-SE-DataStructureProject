#include<iostream>
#include<string>
using namespace std;

class List;

class LinkNode
{
	friend class List;//申明友元为链表类
private:
	int studentID;//考生考号
	string studentName;//姓名
	string studentGender;//性别
	int studentAge;//年龄
	string studentCategory;//报考科目
	LinkNode* link;//指向下一节点的指针
};

class List
{
public:
	List();//构造函数
	~List();//析构函数
	void Input(int studentNumber);//输入构建链表
	void Display()const;//输出
	void Insert(int position);//插入
	void Delete(int position);//删除
	void Change(int ID);//修改
	void Find(int ID)const;//查找
private:
	int listLength;//链表长度
	LinkNode* first;//头节点
};


List::List()
{
	first = new LinkNode;
}

List::~List() 
{
	LinkNode* q;
	while (first->link != nullptr)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	delete first;
}

void List::Input(int studentNumber)
{
	LinkNode* newNode, * last;//创立新节点和尾结点指针
	last = first;
	for (int i = 0; i < studentNumber; i++)//根据输入人数构建链表
	{
		newNode = new LinkNode;
		last->link = newNode;
		last = newNode;
		cin >> newNode->studentID >> newNode->studentName >> newNode->studentGender >> newNode->studentAge >> newNode->studentCategory;
	}
	listLength = studentNumber;
}

void List::Display() const
{
	LinkNode* current;
	current = first->link;
	cout <<"考号"<< "    "
		<<"姓名"<< "    "
		<<"性别"<< "    "
		<<"年龄"<< "    "
		<<"报考类别"<< "    "
		<< endl;
	while (current != nullptr)//依次输出
	{
		cout << current->studentID << "       "
			<< current->studentName << "    "
			<< current->studentGender << "       "
			<< current->studentAge << "    "
			<< current->studentCategory << "    "
			<< endl;
		current = current->link;
	}
}

void List::Find(int ID) const
{
	LinkNode* current = first->link;
	while (current != nullptr && current->studentID != ID)
	{
		current = current->link;
	}//查找并输出
	if (current != nullptr)
	{
		cout << current->studentID << "       "
			<< current->studentName << "    "
			<< current->studentGender << "       "
			<< current->studentAge << "    "
			<< current->studentCategory << "    "
			<< endl;
	}
	//找不到
	else
	{
		cout << "该考生号不存在" << endl;
	}
}


void List::Insert(int position)
{
	if (position > listLength + 1)//位置出错
	{
		cout << "该位置不存在" << endl;
		return;
	}
	LinkNode* current = first;
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄以及报考类别！" << endl;
	LinkNode* newNode = new LinkNode;
	cin >> newNode->studentID >> newNode->studentName >> newNode->studentGender >> newNode->studentAge >> newNode->studentCategory;
	for (int i = 0; i < position - 1; i++)//寻找插入位置
	{
		current = current->link;
	}
	newNode->link = current->link;
	current->link = newNode;
	listLength++;
}


void List::Delete(int position)
{
	if (position > listLength)//位置不存在
	{
		cout << "该位置不存在" << endl;
		return;
	}
	LinkNode* current = first, * temp;
	for (int i = 0; i < position - 1; i++)//找到位置
	{
		current = current->link;
	}
	//删除操作
	temp = current->link;
	cout << "你删除的考生信息是：";
	cout << temp->studentID << "       "
		<< temp->studentName << "    "
		<< temp->studentGender << "       "
		<< temp->studentAge << "    "
		<< temp->studentCategory << "    "
		<< endl;
	current->link = temp->link;
	delete temp;
}


void List::Change(int ID)
{
	LinkNode* current = first->link;
	while (current != nullptr && current->studentID != ID)
	{
		current = current->link;
	}//找到该位置并修改
	if (current != nullptr)
	{
		cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！" << endl;
		cin >> current->studentID >> current->studentName >> current->studentGender >> current->studentAge >> current->studentCategory;
	}//找不到该位置
	else
	{
		cout << "该考生号不存在" << endl;
	}
}


int main()
{
	int number, p, operation;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	cin >> number;
	while (number <= 0)//如果输入不规范
	{
		cout << "请输入一个自然数" << endl;
		cout << "请输入考生人数：";
		cin >> number;
	}

	cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！" << endl;
	List mylist;
	mylist.Input(number);//建立链表
	mylist.Display();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cout << "请选择您要进行的操作:";
	cin >> operation;
	while (operation != 0)//分支选择
	{
		if (operation == 1)
		{
			cout << "请输入你要插入的考生位置：";
			cin >> p;
			mylist.Insert(p);
			mylist.Display();
		}
		if (operation == 2)
		{
			cout << "请输入你要删除的考生位置：";
			cin >> p;
			mylist.Delete(p);
			mylist.Display();
		}
		if (operation == 3)
		{
			cout << "请输入你要查找的考生考号：";
			cin >> p;
			mylist.Find(p);
			mylist.Display();
		}
		if (operation == 4)
		{
			cout << "请输入你要修改的考生考号：";
			cin >> p;
			mylist.Change(p);
			mylist.Display();
		}
		if (operation == 5)
		{
			mylist.Display();
		}
		if (operation > 5 || operation < 0)//不在选择中
		{
			cout << "不存在该操作" << endl;
		}
		cout << "请选择您要进行的操作:";
		cin >> operation;
	}
}
