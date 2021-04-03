/*
 * @Author: your name
 * @Date: 2021-04-01 21:37:44
 * @LastEditTime: 2021-04-02 10:24:44
 * @LastEditors: Please set LastEditors
 * @Description: 双向链表
 * @FilePath: \CHAPTER3 LIST\DoubleLinkList.c
 */

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

// #include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0


#define MAX_SIZE 20
typedef int Status;
typedef int ElementType;

Status visit(ElementType e)
{
    printf("%d",e);
    return OK;
}

typedef struct Node
{
    ElementType data;
    struct Node* next;
    struct Node* previous;
}Node;

typedef  Node *LinkList;

// 初始化
Status InitList(LinkList* L)
{
    *L = (LinkList)malloc(sizeof(Node));        // 头结点的地址，*L就是头指针
    if(!(*L))           // 如果内存分配失败
    {
        return ERROR;
    }
    (*L)->next = NULL;                          // 头结点的next = NULL
    (*L)->previous = NULL;                      // 
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{ 
    if(!(L->next) && !(L->previous))            // 两个指针均为NULL
            return 1;
    else
            return 0;
}

Status ClearList(LinkList *L)           // *L代表首结点的地址
{ 
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
    (*L)->previous = NULL;                          
	return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    int i=0;
    Node* p=L->next; /* p指向第一个结点 */
    while(p)                        
    {
        i++;
        p=p->next;
    }
    return i;
}

/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L,int i,ElementType *e)
{
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{   
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if ( !p || j>i ) 
		return ERROR;  /*  第i个元素不存在 */
	*e = p->data;   /*  取第i个元素的数据 */
	return OK;
}

int LocateElem(LinkList L,ElementType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) /* 找到这样的数据元素 */
                return i;
        p=p->next;
    }

    return 0;
}

/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L,int i,ElementType e)
{ 
	// int j;
	// Node* p,s;
	// p = *L;   
	// j = 1;
	// while (p && j < i)     /* 寻找第i-1个结点 */
	// {
	// 	p = p->next;
	// 	++j;
	// } 
    int length =ListLength(*L);         // 先获取长度

    if(i<1 || i>ListLength(*L)+1)
        return 0;
    // 第二种方法。，找到第i-1个节点
    Node* p_1 = *L;             // 头结点的地址
    for(int j  = 1;j<=i-1;j++)      // 执行几次得到第几个节点的地址
    {
        p_1 = p_1->next;
    }
    // 指向i-1次，P_1代表的是i-1个节点的地址
    Node* p = p_1->next;


	if (!(p_1) ) 
		return ERROR;   /* 第i个元素不存在 */
    
    // 创建新节点
    Node* s;
	s = (LinkList)malloc(sizeof(Node));  /*  生成新结点(C语言标准函数) */
	s->data = e;  
	s->next = p_1->next;      /* 将p的后继结点赋值给s的后继  */
    s->previous = p_1;
	p_1->next = s;          /* 将s赋值给p的后继 */
    
    // 如果插入的位置大于当前长度，那么不需要下面这句
    if(i<=length)
        p->previous = s;        // 原始i的前继
    
	return OK;
}

// 删除第i个节点，并给e
Status ListDelete(LinkList *L,int i,ElementType *e) 
{ 

    // 1.找到第i-1个节点的地址
    Node* p  = *L;
    for(int j = 1;j<=i-1;j++){
        p = p->next;
    }
    // 此时，p代表的是i-1的地址
	if (!(p->next))                 // 判断要删除的第i个元素是否存在
	    return ERROR;           /* 第i个元素不存在 */
	Node* q = p->next;                // i的地址
    Node* q_1 = q->next;              // i+1的地址
	p->next = q->next;			/* 将q的后继赋值给p的后继 */

    // 如果不是删除的最后一个元素，那么执行下面的
    if(q->next)
        q_1->previous = p;          // 将i-1的地址赋值给i+1的前继
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;         // 第一个节点的地址
    while(p)
    {
        visit(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的双链线性表L（头插法） */
void CreateListHead(LinkList *L, int n) 
{
	Node* p;
	int i;
	srand(time(0));                         /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  先建立一个带头结点的单链表 */
    (*L)->previous = NULL;
	for (i=0; i<n; i++) 
	{
		p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;    
        p->previous = (*L);                 // 该节点的前继为首节点

        // 如果不是插入第一个节点，那么执行下面
        if(i != 0)
            (*L)->next->previous = p;           // 将新增节点的地址赋值给原始第一个节点的前继
		(*L)->next = p;						/*  插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的双链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n) 
{
	LinkList p,r;
	int i;
	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */            // 代表首节点的地址
	r=*L;                                /* r为指向尾部的结点 */
	for (i=0; i<n; i++) 
	{
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;           /*  随机生成100以内的数字 */
        p->previous = r;
        // p->next = NULL;
		r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       /* 表示当前链表结束 */
}


int main()
{        
    LinkList L;
    ElementType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));
    for(j=1;j<=5;j++)
        i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L); 

    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("ListLength(L)=%d \n",ListLength(L));

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=LocateElem(L,j);
            if(k)
                    printf("第%d个元素的值为%d\n",k,j);
            else
                    printf("没有值为%d的元素\n",j);
    }
    

    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
            i=ListDelete(&L,j,&e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L); 

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L); 

    i=ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L); 
    
    i=ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L); 


    return 0;
}


