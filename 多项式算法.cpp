// ����ʽ�㷨.cpp : Defines the entry point for the console application.
//

#include"stdafx.h"
#include <iostream>  
using namespace std;
 
class Node {   //�������ʽ�Ĵ洢�ṹ
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

void  CreatPolynomial(Node *&head, int n)        //  ���ɴ���ͷ���ĵ�������ͷ�����������n�����  
{
	head = (Node *)new Node;
	head->coef = 0;
	head->expn = 0;
	head->next = NULL;                           //  ��ʼ��ͷ���  
	cout << "���������ϵ����ָ����" << endl;
	Node *p = head;
	for (int i = 0; i < n; i++) {
		p->next = (Node *)new Node;  //  �����½�㣬β������������  
		p = p->next;
		cin >> p->coef >> p->expn;
		p->next = NULL;
	}
}
void  SortPloy(Node*&L){ //��������
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
	if (head->next == NULL)                           //  �����0ʱֱ�����0  
		putchar('0');
	else {
		for (Node *p = head->next; p != NULL; p = p->next) {
			if (p != head->next && p->coef >0)      //  ��p��������ָ���ϵ��Ϊ��ʱ�����'+'  
				putchar('+');                       //  ֮ǰֻ�ж���p->coef >0  
 
			if (p->coef == 1) {                       //  ϵ��Ϊ1��-1ʱ���⴦��  
				if (p->expn == 0)
					putchar('1');                   //  �ж���������д��һ��  
			}                                       // if(p->coef == 1 && p->expn == 0) putchar('1');  
			else if (p->coef == -1)
				putchar('-');
			else
				cout << p->coef;
 
			switch (p->expn) {                        //  ָ��Ϊ0��1ʱ���⴦��  
			case 0: break;
			case 1: putchar('x'); break;
			default:
				p->expn < 0 ? printf("x^(%d)", p->expn) : printf("x^%d", p->expn);  //  ָ��С��0ʱ������  
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
 
void  AddPolynomial(Node *&pA, Node *&pB)        //  �������������ͷָ��  
{
	
	Node *ha = pA;
	Node *hb = pB;
	Node *qa = ha->next;                     //  ha, hb�ֱ����qa, qb�ĺ�һλ��  
	Node *qb = hb->next; //  qa, qb�ֱ�ָ��Pa, Pb�е�ǰ�Ƚ�Ԫ��  
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
				ha->next = ha->next->next;     //  ɾ����Ϊ0�Ľ�㣬ha���䣬����qa��һλ��  
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
			hb->next = hb->next->next;         //  ɾ��qbָ��Ľ��  
			qb->next = ha->next;              //  ��qb����ha��qaǰ  
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

void  SubPolynomial(Node *&pA, Node *&pB)        //  �������������ͷָ��  
{
	
	Node *ha = pA;
	Node *hb = pB;
	Node *qa = ha->next;                     //  ha, hb�ֱ����qa, qb�ĺ�һλ��  
	Node *qb = hb->next;                    //  qa, qb�ֱ�ָ��Pa, Pb�е�ǰ�Ƚ�Ԫ��  
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
			qa = qa->next;                       //  ��ha = ha->next;  
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
				ha->next = ha->next->next;     //  ɾ����Ϊ0�Ľ�㣬ha���䣬����qa��һλ��  
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
			hb->next = hb->next->next;         //  ɾ��qbָ��Ľ��  
			qb->next = ha->next;              //  ��qb����ha��qaǰ  
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
	cout <<" ��ѡ��Ҫ�Զ���ʽ���еĲ��������������в���ѡ��ǰ�Ĵ����Խ��иò�����"<<endl;
	while(1)
	{
     	cout << "1.�Զ���ʽA,B��ӡ�" << endl;
    	cout << "2.�Զ���ʽA,B�����" << endl;
    	cin >> m;
		while(m!=1&&m!=2) {
			cout<<"����ѡ������������������������:"<<endl;
			cin>>m;
			if(m==1||m==2) break;
		}
		break;
	}
	if(m==1)
	{
		    cout << "������A��������" << endl;
	        cin >> LenA;
			CreatPolynomial(A, LenA);//  ����A���� 
			SortPloy(A);
        	cout << "������B��������" << endl;         //  ����B����  
        	cin >> LenB;
			CreatPolynomial(B, LenB);
			SortPloy(B);
			cout << " A = ";                          //  ���A����  
			PrintPolynomial(A);
			cout << " B = ";                          //  ���B����  
			PrintPolynomial(B);
      		AddPolynomial(A, B);                        //  A = A + B  
			cout << "A+B= ";
			PrintPolynomial(A);                         //  �����  
			cout << endl;
	}
	if(m==2)
	{       cout << "������A��������" << endl;
        	cin >> LenA;
        	CreatPolynomial(A, LenA); //  ����A���� 
			SortPloy(A);
	        cout << "������B��������" << endl;         //  ����B����  
        	cin >> LenB;
			CreatPolynomial(B, LenB);
			SortPloy(B);
			cout << " A = ";                          //  �������ʽA  
			PrintPolynomial(A);
			cout << " B = ";                          //  �������ʽB 
			PrintPolynomial(B);
        	SubPolynomial(A, B);                        // ���� A = A - B  
			cout << "A-B= ";
			PrintPolynomial(A);                         //  �����A-B  
			cout << endl;
	}

	return 0;
}
