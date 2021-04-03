/*
 * @Author: your name
 * @Date: 2021-04-01 14:18:09
 * @LastEditTime: 2021-04-01 21:39:59
 * @LastEditors: Please set LastEditors
 * @Description: 线性表 链式存储
 * @FilePath: \MyCode\CHAPTER3 LIST\LinkList.c
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
}Node;

typedef  Node *LinkList;

// 初始化
Status InitList(LinkList* L)
{
    *L = (LinkList)malloc(sizeof(Node));        // 头结点的地址，L就是头指针
    if(!(*L))
    {
        return ERROR;
    }
    (*L)->next = NULL;                          // 头结点的next = NULL
    return OK;
}

// 判断LinkList是否为空
Status ListEmpty(LinkList L)
{
    if(L->next == NULL)
    {
        return 1;
    }
    return 0;
}

// 初始条件：顺序链表L已存在，操作结果：将L重置为空表
Status ClearList(LinkList* L)
{
    LinkList p,q;
    p = (*L)->next;                  // (*L)代表头结点的地址，也就是头指针，p为第一个节点的地址
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;              // 头指针指向空


    return 1;
}

// 初始条件：顺序链表L已经存在，操作结果：返回L中数据元素个数
int ListLength(LinkList L)
{
    int  i = 0;
    Node* p = L->next;            // L代表头结点
    while(p)
    {
        i++;
        p = p->next;
    }
    return i;
}

// 初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
// 操作结果：用e返回L中第i个数据元素的值
Status GetElem(LinkList L,int i , ElementType* e)
{
    Node* p = L;          // p:第0个元素节点的地址，也就是首节点的地址
    if(p->next ==NULL)          // 空表
        return 0;
    if(i<1 || i>ListLength(L))          // 超出index范围
        return 0;
    for (size_t k = 1; k <= i; k++)         // 执行一次，指针向后移动一次，最终找到第i个元素的地址
    {
        p = p->next;
    }
    *e = p->data;
    return 1;
    
}

// 初始条件：顺序线性表已经存在
// 操作结果：返回L中第1个与e满足关系（相等）的数据元素的位序
// 若不存在，则返回0
int LocateElem(LinkList L,ElementType e)
{
    Node* p = L->next;        // p代表第一个节点的地址
    int i = 1;
    while(p){
        if(p->data == e)
        {
            return i;
        }
        else
        {
            p = p->next;
            i++;
        }
    }
    return 0;

}

// 初始条件：顺序线性表L已存在，1<=i<=ListLength(ListLength(L)
// 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度+1
Status ListInsert(LinkList* L,int i,ElementType e)
{
    Node* p = *L;
    if(i<1)
    {
        return 0;
    }
    int k = 0;
    while(k<(i-1)){         // 找到第i-1个元素
        p=p->next;
        k++;
    }
    // 此时p指向第i-1个节点
    Node* p_i_sub_1 = p;            // 保存i-1节点的地址

    // 获取i节点的地址
    Node* p_i = p->next;
    
    // 新建一个节点
    Node* new_node = (Node* )malloc(sizeof(Node));
    new_node->data = e;
    new_node->next = p_i;

    p_i_sub_1->next = new_node;
    return 1;

}

// 初始条件：1<=i<=ListLength(L)
// 操作结果：删除L的第i个元素，并用e返回值，长度-1
Status ListDelete(LinkList* L,int i,ElementType *e){
    int j = 0;
    Node* p = *L;           // 首节点的地址
    while(p->next && j<i-1)
    {
        p = p->next;
        j++;
    }
    // 此时，p代表的是第i-1个节点的地址

    if(!(p->next))
    {
        return ERROR;
    }

    *e = p->next->data;     
    Node* q = p->next;       // 第i个元素的地址
    p->next = q->next;
    free(q);

    return 1;


}

// 遍历L
Status ListTraverse(LinkList L)
{
    Node* p = L->next;     // 第一个节点
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n----------------------\n");
    return 1;
}

// 随机产生n个元素的值，建立带表头节点的单线性链表（头插法）
Status CreateListHead(LinkList* L,int n)
{
    Node* p;
    // int i ;
    srand(time(0));
    (*L)->next = NULL;          // 头结点
    for(int i=1;i<=n;i++)
    {
        p = (Node*)malloc(sizeof(Node));
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;         // 头结点的下一个就是新增加的p节点
    }
}

// 尾插法
Status CreateListTail(LinkList* L,int n)
{
    LinkList p,r;          // r代表指向尾部的指针
    int i;
    srand(time(0));
    (*L)->next = NULL;                          
    r = *L;              // r指向头结点，代表是空链表
    for(int i = 1;i<=n;i++)
    {
        p = (Node*)malloc(sizeof(Node));
        p->data = rand()%100+1;
        // p->next = NULL;
        r->next = p;
        // 更新尾指针
        r = p;
    }

    r->next = NULL;

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

    // printf("a1:%d",L->next->data);           // 第一个节点的data
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

