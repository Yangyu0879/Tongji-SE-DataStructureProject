#include<iostream>
using namespace std;

class List;

class LinkNode
{
	friend class List;//申明友元
private:
	int number;//节点中数字
	LinkNode* link;//节点的下一个元素
};


class List
{
public:
	List();//构造函数
	~List();//析构函数
	bool Construction();//建立链表
	void Union(List& a, List& b);//求交集运算
	void Display();//输出
	LinkNode* Gethead();//取头节点
private:
	LinkNode* first;//链表头节点
};
//构造函数构造了一个空的头节点放在节点的第一个位置使得链表成为了一个，
//带附加头结点的链表，方便进行查找，插入等一系列的操作，使得程序更加简洁。
List::List()
{
	first = new LinkNode;
}

List::~List()
{

}
//根据输入内容创建非降序的序列，收到输入后，
//如果这个输入的值大于上一个输入的值（开头默认为0）且不是非正整数时，
//开辟一个节点空间，将该数字链入链表之中。否则，停止输入并报出错误信息。
//当输入的数字为-1时，则认为该序列输入结束。
//当构建不成功时，输出0，成功时输出1。
bool List::Construction()
{
	LinkNode* newNode;
	LinkNode* last;
	last = first;
	int n, k = 0;
	cin >> n;
	while (n != -1)
	{
		if (k > n&& k >= 0)//错误判断
		{
			cout << "序列有误" << endl;
			return 0;
		}
		k = n;
		newNode = new LinkNode;//建立新节点
		last->link = newNode;
		last = newNode;
		newNode->number = n;
		cin >> n;
	}
	last->link = nullptr;
	return 1;
}
//函数返回值为附加头节点的下一个节点地址。
LinkNode* List::Gethead()
{
	return this->first->link;
}
//此为核心功能，交集函数的参数为两个有序链表的地址。
//首先，通过调用获取头节点的函数得到跳过附加头节点的第一个节点的地址。传进来的两个有序链表都需要这样的一步操作。
//随后开始比较节点，如果两个链表都没有为空节点，则比较两节点内容，如果相等，则把该内容链入第三个链表中，否则舍弃，比较两者内容大小。
//如果a链表内容大，则b链表指向下一节点，反之亦然。直到两个链表中有一个为空。
void List::Union(List& a, List& b)
{
	LinkNode* current1 = a.Gethead();
	LinkNode* current2 = b.Gethead();
	LinkNode* current3 = first;
	LinkNode* newNode;
	while (current1 != nullptr && current2 != nullptr)
	{
		if (current1->number == current2->number)//相等情况
		{
			newNode = new LinkNode;
			newNode->number = current1->number;
			current3->link = newNode;
			current3 = newNode;
			current1 = current1->link;
			current2 = current2->link;
		}
		else if (current1->number < current2->number)//A大
		{
			current1 = current1->link;
		}
		else if (current1->number > current2->number)//B大
		{
			current2 = current2->link;
		}
	}
	current3->link = nullptr;//末尾链入空
}

//从第一个节点开始依次输出内容，如果链表为空，则输出NULL，否则输出所有内容。
void List::Display()
{
	LinkNode* current = this->Gethead();
	if (current == nullptr)//为空情况
	{
		cout << "NULL";
	}
	else//不为空，依次输出
	{
		while (current != nullptr)
		{
			cout << current->number << " ";
			current = current->link;
		}
	}
}
//首先申明三个链表，a,b,c。然后构建a和b链表，如果构建成功则继续取交集的函数并输出c的内容，否则，输出错误信息后结束该程序
int main()
{
	List a, b, c;
	if (a.Construction() && b.Construction())//判断是否成功建立
	{
		c.Union(a, b);
		c.Display();
	}
}