/*
 * @Author: your name
 * @Date: 2021-04-01 17:24:22
 * @LastEditTime: 2021-04-01 21:19:06
 * @LastEditors: Please set LastEditors
 * @Description: 静态链表---》不使用指针实现链式存储
 * @FilePath: \CHAPTER3 LIST\StaticList.c
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAX_SIZE 1000
typedef int Status;
typedef char ElementType;

Status visit(ElementType c)
{
    printf("%c",c);
    return 1;
}

// 线性表的链式存储结构
typedef struct
{
    ElementType data;
    int cur;            // 游标 （Cursor），为0时代表无指向
}Component,StaticLinkList[MAX_SIZE];

// 初始化
Status InitList(StaticLinkList space)
{
    for(int i =0;i<MAX_SIZE-1;i++)
    {
        space[i].cur=i+1;
    }

    space[MAX_SIZE-1].cur = 0;      // 最后一个元素的cur=0，类似于头指针，指向第一个元素
    return 1;
}

// 若备用空间链表非空，则返回分配的结点下标，否则返回0
int Malloc_SSL(StaticLinkList space)
{
    int i = space[0].cur;

    if(space[0].cur)            // 如果还有备用链表。
        space[0].cur = space[i].cur;            // 更新第一个元素的cur
    return i;
}

// 将下标为k的空闲结点回收到备用链表
void Free_SSL(StaticLinkList space,int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// 返回List长度
int ListLength(StaticLinkList L)
{
    int i =0;
    int j = L[MAX_SIZE-1].cur;          // 有点像头指针，指向第一个元素
    while(j)
    {
        i++;
        j = L[j].cur;
        
    }
    return i;

}

// 在第i个元素处插入元素e
Status ListInsert(StaticLinkList L,int i,ElementType e)
{
    if(i<1 || i>ListLength(L)+1)
    {
        return 0;
    }



    // 找到第i-1个元素
    int p = MAX_SIZE-1;              // 最后一个元素的下标
    for(int n = 1;n<=i-1;n++)         // 执行i-1次
    {
        p = L[p].cur;
    }

    // 此时 p代表i-1的地址
    int q = L[p].cur;            // i的地址

    int j = Malloc_SSL(L);
    if(j)                       // 还有空间
    {
        L[j].data = e;
        L[j].cur = q;               // 新增元素的cur为原来的i元素的地址

        L[p].cur = j;                // i-1----->j(新增元素)

        return 1;
    }
    return 0;


}

Status ListDelete(StaticLinkList L,int i)
{
    if(i<1 || i>ListLength(L))
    {
        return 0;
    }

    int p = MAX_SIZE-1;
    // 先找到i-1的下标
    for(int n=1;i<=i-1;n++)
    {
        p = L[p].cur;
    }

    // 此时p代表i-1个元素的下标
    int q = L[p].cur;       // q代表i元素的下标
    L[p].cur = L[q].cur;

    Free_SSL(L,q);
    return 1;
}

// 遍历
Status ListTraverse(StaticLinkList L)
{
    int j = 0;
    
    int  p = L[MAX_SIZE-1].cur;             // 第一个元素的下标
    while(p)
    {
        j++;
        visit(L[p].data);
        p = L[p].cur;
    }
    
    printf("\n--------------\n");
    return 1;
    

}

int main()
{
    StaticLinkList L;
    Status i;
    i=InitList(L);
    printf("初始化L后：L.length=%d\n",ListLength(L));

    i=ListInsert(L,1,'F');
    i=ListInsert(L,1,'E');
    i=ListInsert(L,1,'D');
    i=ListInsert(L,1,'B');
    i=ListInsert(L,1,'A');

    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L); 

    i=ListInsert(L,3,'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L); 

    i=ListDelete(L,1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L); 

    printf("\n");

    return 0;
}



