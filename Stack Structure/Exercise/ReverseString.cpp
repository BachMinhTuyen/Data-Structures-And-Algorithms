#include<stdio.h>
#include<conio.h>
#include<string.h>
struct SNode
{
	int info;
	SNode* next;
};
struct Stack
{
	SNode* top;
};
void initStack(Stack& stack);
int isEmpty(Stack stack);
SNode* createSNode(int x);
void pushStack(Stack& s, SNode* p);
int popStack(Stack& s);
void daoNguocChuoi(char str[]);

int main()
{
	char str[100];
	printf("\nNhap chuoi: ");
	rewind(stdin);
	gets_s(str);
	printf("\nChuoi ban dau  : ");
	printf("%s", str);
	printf("\nChuoi dao nguoc: ");
	daoNguocChuoi(str);

	_getch();
	return 0;
}
void initStack(Stack& stack)
{
	stack.top = NULL;
}
int isEmpty(Stack stack)
{
	if (stack.top == NULL)
		return 1;//stack rỗng
	return 0;//stack không rỗng
}
SNode* createSNode(int x)
{
	SNode* p = new SNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho");
		_getch();
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}
void pushStack(Stack& s, SNode* p)
{
	if (p == NULL)
		return;

	if (isEmpty(s))
		s.top = p;
	else
	{
		p->next = s.top;
		s.top = p;
	}
}
int popStack(Stack& s)
{
	SNode* p;
	int x;
	if (!isEmpty(s))
	{
		p = s.top;
		s.top = s.top->next;
		x = p->info;
		delete p;
		return x;
	}
}
void daoNguocChuoi(char str[])
{
	Stack s;
	initStack(s);
	int k, len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		SNode* p = createSNode(str[i]);
		pushStack(s, p);
	}
	for (int i = 0; i < len; i++)
	{
		k = popStack(s);
		printf("%c", k);
	}
}