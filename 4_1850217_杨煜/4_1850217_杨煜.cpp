#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int flag = 1;

template<class T>
class myStack
{
public:
	myStack(int sz = 100);//构造函数，默认长度100
	~myStack() { delete[]elements; }//析构函数
	void push(const T& x);//压栈
	T pop();//弹出
	T getTop();//获取顶点
	bool isEmpty() { return(top == -1) ? true : false; }//是否为空
	bool isFull() { return(top == maxSize - 1) ? true : false; }//是否为满
	int top;//顶点
private:
	T* elements;//数组指针
	int maxSize;//栈最大大小
};
//构造函数接受一个默认的参数100，置top为-1，开辟数组空间。
template<class T>
myStack<T>::myStack(int sz)
{
	top = -1;
	maxSize = sz;
	elements = new T[maxSize];
}
//压栈函数接受要压入的数，将一个新的数据压入栈中，使顶点指针指向这个数据。如果为满，则操作失败。
template<class T>
void myStack<T>::push(const T& x)
{
	if (top == maxSize-1)//判断是否满了
	{
		cerr << "错误";
		flag = 0;
	}
	else
	{
		elements[++top] = x;//压栈
	}
};
//弹出函数返回值为被弹出栈的值，同时指针左移，指向前一个数。如果为空，则失败。
template<class T>
T myStack<T>::pop()
{
	if (top == - 1)//判断是否空了
	{
		cerr << "错误";
		flag = 0;
	}
	else
	{
		return elements[top--];//弹出
	}
}

template<class T>
T myStack<T>::getTop()
{
	return elements[top];
}
//计算函数接受三个参数，两个为数字，一个为运算符，根据运算符做不同性质的运算，返回结果。
//其中使用switch来进行分支运算。
int Cal(char a, int b, int c)//运算函数，a为运算符,b、c分别为两数
{
	if (a == '(')
	{
		flag=0;
		cout<<"错误";
	}
	switch (a)//根据符号不同，分别做运算
	{
	case '+':
		return (b + c);
		break;
	case '-':
		return (b - c);
		break;
	case '*':
		return (b * c);
		break;
	case '/':
		return (b / c);
		break;
	case '^':
		return pow(b,c);
		break;
	case '%':
		return (b % c);
		break;
	}
}

//首先创立两个栈实例，一个为运算符栈，一个为数字栈。读入中缀表达式，
//首先判断，第一个数字是否为负数，即完成单目运算符 - ，如果是则通过运算将其变成负数。
//随后则进行表达式的处理，将数字都存入数字栈。
//读到运算符时，如果运算符栈不为空，则比较运算符优先级，如果前者为高，则优先进行计算。
//碰到(入栈，碰到)则进行运算直到运算符栈弹出的内容为（。
//最后则可以完成该中缀表达式的求值。
int main(void)
{
	myStack<int> stack1;//建立运算符，数字栈
	myStack<char> stack2;
	char isContinue = 'y';
	while (isContinue == 'y')//判别是否继续
	{
		cout << "请输入表达式:" << endl;
		int i = 0;
		string str;//接受表达式
		cin >> str;
		char a;
		int b, c;
		if (str[0] == '-')//判断是否为负数
		{
			stack1.push(-(str[i + 1] - '0'));
			i += 2;
		}
		while (str[i] != '=')//判断是否结束
		{

			if (str[i] == '-' && ((str[i - 1] - '0' < 0 || str[i - 1] - '0' > 9))&&str[i-1]!=')')//判断是否为负数
			{
				stack1.push(-(str[i + 1] - '0'));
				i += 2;
				continue;
			}
			if (str[i] == '+' || str[i] == '-')//判断加减法
			{
				if (stack2.top == -1)//判断运算符栈
				{
					stack2.push(str[i]);
				}
				else
				{
					while (stack2.getTop() == '+' || stack2.getTop() == '-' || stack2.getTop() == '*' || stack2.getTop() == '/' || stack2.getTop() == '^' || stack2.getTop() == '%')//判断优先级
					{
						a = stack2.pop();
						c = stack1.pop();
						b = stack1.pop();
						stack1.push(Cal(a, b, c));
					}
					stack2.push(str[i]);//运算结果入栈
				}
			}
			else if (str[i] == '*' || str[i] == '/' || str[i] == '%')////判断乘除法
			{
				if (stack2.top == -1)
				{
					stack2.push(str[i]);
				}
				else
				{
					while (stack2.getTop() == '*' || stack2.getTop() == '/' || stack2.getTop() == '^' || stack2.getTop() == '%')//判断优先级
					{
						a = stack2.pop();
						c = stack1.pop();
						b = stack1.pop();
						stack1.push(Cal(a, b, c));
					}
					stack2.push(str[i]);
				}
			}
			else if (str[i] == '^')
			{
				if (stack2.top == -1)
				{
					stack2.push(str[i]);
				}
				else
				{
					while (stack2.getTop() == '^')
					{
						a = stack2.pop();
						c = stack1.pop();
						b = stack1.pop();
						stack1.push(Cal(a, b, c));
					}
					stack2.push(str[i]);
				}
			}
			else if (str[i] == '(')//判断括号
			{
				stack2.push(str[i]);
			}
			else if (str[i] == ')')
			{
				while (stack2.getTop() != '(')
				{
					a = stack2.pop();
					c = stack1.pop();
					b = stack1.pop();
					stack1.push(Cal(a, b, c));
					if (flag == 0)
					{
						break;
					}
				}
				stack2.pop();
			}
			else//多位的整数
			{
				int t = i;
				int k = 0;
				while (str[t] - '0' >= 0 && str[t] - '0' <= 9)
				{
					t++;
				}
				for (int p = i; p < t; p++)
				{
					k += (str[p] - '0') * (int)pow(10, t - p - 1);
				}
				stack1.push(k);
				i = t;
				continue;
			}
			i++;
		}
		if (flag == 1)
		{
			while (stack2.top != -1)//计算结果
			{
				a = stack2.pop();
				c = stack1.pop();
				b = stack1.pop();
				stack1.push(Cal(a, b, c));
			}
			cout << stack1.getTop() << endl;
		}
		cout << "是否继续（y，n）？";
		cin >> isContinue;
	}
	return 0;
}
