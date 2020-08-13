#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int flag = 1;

template<class T>
class myStack
{
public:
	myStack(int sz = 100);//���캯����Ĭ�ϳ���100
	~myStack() { delete[]elements; }//��������
	void push(const T& x);//ѹջ
	T pop();//����
	T getTop();//��ȡ����
	bool isEmpty() { return(top == -1) ? true : false; }//�Ƿ�Ϊ��
	bool isFull() { return(top == maxSize - 1) ? true : false; }//�Ƿ�Ϊ��
	int top;//����
private:
	T* elements;//����ָ��
	int maxSize;//ջ����С
};
//���캯������һ��Ĭ�ϵĲ���100����topΪ-1����������ռ䡣
template<class T>
myStack<T>::myStack(int sz)
{
	top = -1;
	maxSize = sz;
	elements = new T[maxSize];
}
//ѹջ��������Ҫѹ���������һ���µ�����ѹ��ջ�У�ʹ����ָ��ָ��������ݡ����Ϊ���������ʧ�ܡ�
template<class T>
void myStack<T>::push(const T& x)
{
	if (top == maxSize-1)//�ж��Ƿ�����
	{
		cerr << "����";
		flag = 0;
	}
	else
	{
		elements[++top] = x;//ѹջ
	}
};
//������������ֵΪ������ջ��ֵ��ͬʱָ�����ƣ�ָ��ǰһ���������Ϊ�գ���ʧ�ܡ�
template<class T>
T myStack<T>::pop()
{
	if (top == - 1)//�ж��Ƿ����
	{
		cerr << "����";
		flag = 0;
	}
	else
	{
		return elements[top--];//����
	}
}

template<class T>
T myStack<T>::getTop()
{
	return elements[top];
}
//���㺯��������������������Ϊ���֣�һ��Ϊ��������������������ͬ���ʵ����㣬���ؽ����
//����ʹ��switch�����з�֧���㡣
int Cal(char a, int b, int c)//���㺯����aΪ�����,b��c�ֱ�Ϊ����
{
	if (a == '(')
	{
		flag=0;
		cout<<"����";
	}
	switch (a)//���ݷ��Ų�ͬ���ֱ�������
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

//���ȴ�������ջʵ����һ��Ϊ�����ջ��һ��Ϊ����ջ��������׺���ʽ��
//�����жϣ���һ�������Ƿ�Ϊ����������ɵ�Ŀ����� - ���������ͨ�����㽫���ɸ�����
//�������б��ʽ�Ĵ��������ֶ���������ջ��
//���������ʱ����������ջ��Ϊ�գ���Ƚ���������ȼ������ǰ��Ϊ�ߣ������Ƚ��м��㡣
//����(��ջ������)���������ֱ�������ջ����������Ϊ����
//����������ɸ���׺���ʽ����ֵ��
int main(void)
{
	myStack<int> stack1;//���������������ջ
	myStack<char> stack2;
	char isContinue = 'y';
	while (isContinue == 'y')//�б��Ƿ����
	{
		cout << "��������ʽ:" << endl;
		int i = 0;
		string str;//���ܱ��ʽ
		cin >> str;
		char a;
		int b, c;
		if (str[0] == '-')//�ж��Ƿ�Ϊ����
		{
			stack1.push(-(str[i + 1] - '0'));
			i += 2;
		}
		while (str[i] != '=')//�ж��Ƿ����
		{

			if (str[i] == '-' && ((str[i - 1] - '0' < 0 || str[i - 1] - '0' > 9))&&str[i-1]!=')')//�ж��Ƿ�Ϊ����
			{
				stack1.push(-(str[i + 1] - '0'));
				i += 2;
				continue;
			}
			if (str[i] == '+' || str[i] == '-')//�жϼӼ���
			{
				if (stack2.top == -1)//�ж������ջ
				{
					stack2.push(str[i]);
				}
				else
				{
					while (stack2.getTop() == '+' || stack2.getTop() == '-' || stack2.getTop() == '*' || stack2.getTop() == '/' || stack2.getTop() == '^' || stack2.getTop() == '%')//�ж����ȼ�
					{
						a = stack2.pop();
						c = stack1.pop();
						b = stack1.pop();
						stack1.push(Cal(a, b, c));
					}
					stack2.push(str[i]);//��������ջ
				}
			}
			else if (str[i] == '*' || str[i] == '/' || str[i] == '%')////�жϳ˳���
			{
				if (stack2.top == -1)
				{
					stack2.push(str[i]);
				}
				else
				{
					while (stack2.getTop() == '*' || stack2.getTop() == '/' || stack2.getTop() == '^' || stack2.getTop() == '%')//�ж����ȼ�
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
			else if (str[i] == '(')//�ж�����
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
			else//��λ������
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
			while (stack2.top != -1)//������
			{
				a = stack2.pop();
				c = stack1.pop();
				b = stack1.pop();
				stack1.push(Cal(a, b, c));
			}
			cout << stack1.getTop() << endl;
		}
		cout << "�Ƿ������y��n����";
		cin >> isContinue;
	}
	return 0;
}
