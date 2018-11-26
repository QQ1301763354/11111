// 多项式算法.cpp : Defines the entry point for the console application.
//

#include"stdafx.h"
#include <iostream>  
using namespace std;
 
class Node {   //定义多项式的存储结构
public:
	float coef;
	int expn;
	Node *next;
	
};
class Poly{
public:
	~Poly();
	void CreatPolynomial(class Node *& ,int);
	void SortPloy(Node*&L);
    void PrintPolynomial(Node *&head);
	char cmp(int,int);
	void AddPolynomial(Node *&pA, Node *&pB);
	void SubPolynomial(Node *&pA, Node *&pB);
};

void  CreatPolynomial(Node *&head, int n)        //  生成带表头结点的单链表，除头结点外另生成n个结点  
{
	head = (Node *)new Node;
	head->coef = 0;
	head->expn = 0;
	head->next = NULL;                           //  初始化头结点  
	cout << "请输入各项系数及指数：" << endl;
	Node *p = head;
	for (int i = 0; i < n; i++) {
		p->next = (Node *)new Node;  //  生成新结点，尾插入生成链表  
		p = p->next;
		cin >> p->coef >> p->expn;
		p->next = NULL;
	}
}
void  SortPloy(Node*&L){ //升幂排序
	Node*p=L->next,*q=p->next;
    int coef,expn;
    while(p!=NULL&&p->next!=NULL){
		while(q!=NULL)
		{
			if(p->expn>q->expn){
				coef=p->coef;
				expn=p->expn;
				p->coef=q->coef;
				p->expn=q->expn;
				q->coef=coef;
				q->expn=expn;
			}
			q=q->next;
		}
		p=p->next;
		q=p->next;
	}
}
void  PrintPolynomial(Node *&head)
{
	if (head->next == NULL)                           //  结果是0时直接输出0  
		putchar('0');
	else {
		for (Node *p = head->next; p != NULL; p = p->next) {
			if (p != head->next && p->coef >0)      //  当p非首项且指向的系数为正时才输出'+'  
				putchar('+');                       //  之前只判定了p->coef >0  
 
			if (p->coef == 1) {                       //  系数为1或-1时特殊处理  
				if (p->expn == 0)
					putchar('1');                   //  判断条件不能写在一起：  
			}                                       // if(p->coef == 1 && p->expn == 0) putchar('1');  
			else if (p->coef == -1)
				putchar('-');
			else
				cout << p->coef;
 
			switch (p->expn) {                        //  指数为0或1时特殊处理  
			case 0: break;
			case 1: putchar('x'); break;
			default:
				p->expn < 0 ? printf("x^(%d)", p->expn) : printf("x^%d", p->expn);  //  指数小于0时打括号  
				break;
			}
		}
	}
	cout << endl;
}

char  cmp(int a, int b)
{
	if (a > b)
		return '>';
	if (a < b)
		return '<';
	return '=';
}
 
void  AddPolynomial(Node *&pA, Node *&pB)        //  传进两个链表的头指针  
{
	
	Node *ha = pA;
	Node *hb = pB;
	Node *qa = ha->next;                     //  ha, hb分别跟在qa, qb的后一位置  
	Node *qb = hb->next; //  qa, qb分别指向Pa, Pb中当前比较元素  
	while (qa && qb)
	{
		float sum = 0;
		int a = qa->expn;
		int b = qb->expn;
		switch (cmp(a, b)) {
 
		case '<':
			ha = qa;
			qa = qa->next;                         
			break;
 
		case '=':
			sum = qa->coef + qb->coef;
			if (sum != 0.0) {
				qa->coef = sum;
				ha = qa;
			}
			else {
				if (ha->next != qa)
					cout << "Error: ha->next != qa" << endl;
				ha->next = ha->next->next;     //  删除和为0的结点，ha不变，还在qa后一位置  
				free(qa);
			}
			if (hb->next != qb)
				cout << "Error: hb->next != qb" << endl;
			hb->next = hb->next->next;
			free(qb);
			qb = hb->next;
			qa = ha->next;
			break;
 
		case '>':
			hb->next = hb->next->next;         //  删除qb指向的结点  
			qb->next = ha->next;              //  将qb插入ha后qa前  
			ha->next = qb;
 
			qb = hb->next;                       //  not qb = ha->next  
			ha = ha->next;
			break;
 
		default:
			cout << "Error!" << endl;
			break;
		}
	}
	if (qb)
		ha->next = qb;
	free(hb);
}

void  SubPolynomial(Node *&pA, Node *&pB)        //  传进两个链表的头指针  
{
	
	Node *ha = pA;
	Node *hb = pB;
	Node *qa = ha->next;                     //  ha, hb分别跟在qa, qb的后一位置  
	Node *qb = hb->next;                    //  qa, qb分别指向Pa, Pb中当前比较元素  
	  while (pB!=NULL) {
		
		pB->coef = (-pB->coef);
		pB = pB->next;
	}
	while (qa && qb)
	{
		float sum = 0;
		int a = qa->expn;
		int b = qb->expn;
		switch (cmp(a, b)) {
 
		case '<':
			ha = qa;
			qa = qa->next;                       //  非ha = ha->next;  
			break;
 
		case '=':
			sum = qa->coef + qb->coef;
			if (sum != 0.0) {
				qa->coef = sum;
				ha = qa;
			}
			else {
				if (ha->next != qa)
					cout << "Error: ha->next != qa" << endl;
				ha->next = ha->next->next;     //  删除和为0的结点，ha不变，还在qa后一位置  
				free(qa);
			}
			if (hb->next != qb)
				cout << "Error: hb->next != qb" << endl;
			hb->next = hb->next->next;
			free(qb);
			qb = hb->next;
			qa = ha->next;
			break;
 
		case '>':
			hb->next = hb->next->next;         //  删除qb指向的结点  
			qb->next = ha->next;              //  将qb插入ha后qa前  
			ha->next = qb;
 
			qb = hb->next;                       //  not qb = ha->next  
			ha = ha->next;
			break;
 
		default:
			cout << "Error!" << endl;
			break;
		}
	}
	if (qb)
		ha->next = qb;
	free(hb);
}
int main( )
{
	Node *A = NULL;
	Node *B = NULL;
	int LenA;
	int LenB;
	int m;
	cout <<" 请选择要对多项式进行的操作：（输入下列操作选项前的代码以进行该操作）"<<endl;
	while(1)
	{
     	cout << "1.对多项式A,B相加。" << endl;
    	cout << "2.对多项式A,B相减。" << endl;
    	cin >> m;
		while(m!=1&&m!=2) {
			cout<<"你所选择的请求代号有误，请重新输入:"<<endl;
			cin>>m;
			if(m==1||m==2) break;
		}
		break;
	}
	if(m==1)
	{
		    cout << "请输入A的项数：" << endl;
	        cin >> LenA;
			CreatPolynomial(A, LenA);//  生成A链表 
			SortPloy(A);
        	cout << "请输入B的项数：" << endl;         //  生成B链表  
        	cin >> LenB;
			CreatPolynomial(B, LenB);
			SortPloy(B);
			cout << " A = ";                          //  输出A链表  
			PrintPolynomial(A);
			cout << " B = ";                          //  输出B链表  
			PrintPolynomial(B);
      		AddPolynomial(A, B);                        //  A = A + B  
			cout << "A+B= ";
			PrintPolynomial(A);                         //  输出和  
			cout << endl;
	}
	if(m==2)
	{       cout << "请输入A的项数：" << endl;
        	cin >> LenA;
        	CreatPolynomial(A, LenA); //  生成A链表 
			SortPloy(A);
	        cout << "请输入B的项数：" << endl;         //  生成B链表  
        	cin >> LenB;
			CreatPolynomial(B, LenB);
			SortPloy(B);
			cout << " A = ";                          //  输出多项式A  
			PrintPolynomial(A);
			cout << " B = ";                          //  输出多项式B 
			PrintPolynomial(B);
        	SubPolynomial(A, B);                        // 计算 A = A - B  
			cout << "A-B= ";
			PrintPolynomial(A);                         //  输出差A-B  
			cout << endl;
	}

	return 0;
}
