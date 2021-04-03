/*
 * @Author: your name
 * @Date: 2021-04-01 09:49:07
 * @LastEditTime: 2021-04-01 11:35:24
 * @LastEditors: Please set LastEditors
 * @Description: 线性表 顺序存储
 * @FilePath: \MyCode\CHAPTER3 LIST\List.c
 */

#include "stdio.h"
#include "stdlib.h"
// #include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int ElementType;

typedef struct 
{
    ElementType data[MAX_SIZE];     // 数组的最大长度
    int length;                     // 线性表当前长度
}SqList;

void visit(ElementType c)
{
    printf("%d",c);
    // return OK;
}

// 线性表初始化
Status InitList(SqList* L)
{
    L->length = 0;
    return OK;
}

// 判断List是否为空
Status ListEmpty(SqList L)
{
    if(L.length == 0)
        return TRUE;
    return FALSE;
}

// 将List置空
Status ClearList(SqList* L)
{
    L->length = 0;
    return OK;
}

// 获取元素
Status GetElem(SqList L,int i ,ElementType* e)
{
    if(L.length==0 || i<1 || i>L.length)
    {
        return ERROR;
    }
    
    *e = L.data[i-1];
    return OK;

}

// 定位元素
int LocateElem(SqList L,ElementType e)
{
    if(L.length == 0 )
        return ERROR;
    
    for (int i=0;i<L.length;i++)
    {
        if(L.data[i] == e)
        {
            return i+1;         // i代表下标；i+1代表位置
        }
    }
    return ERROR;
}

// 插入元素
Status ListInsert(SqList *L,int i,ElementType e)
{
    if(L->length == MAX_SIZE)
        return ERROR;
    
    if(i<1 || i>L->length+1)        // 如果不在1~length+1的范围内,那么不能插入，因为如果是在length+2插入，肯定就不连续了，不符合定义
    {
        return ERROR;
    }

    // 如果是最后一个表尾插入元素
    if(i == L->length+1)
    {
        L->data[L->length] = e;
        L->length++;
        return OK;
    }

    // 如果不是表尾部插入元素---》插入范围：[1,length]
    for(int j = L->length;j>=i;j--)         // 从尾部往前遍历
    {
        L->data[j+1-1] = L->data[j-1];
    }
    L->data[i-1] = e;                       // 修改第i个位置的元素
    L->length++;

    return OK;



    
}


// 删除元素
Status ListDelete(SqList* L,int i,ElementType e)
{
    if(L->length == 0 || i<1 || i>L->length)
        return ERROR;
    
    if(i == L->length)
    {
        e = L->data[i-1];
        L->length--;
        return OK;
    }

    // 不是最后一个元素
    e = L->data[i-1];
    for(int j = i+1;j<=L->length;j++)
    {
        L->data[j-1-1] = L->data[j-1];
    }
    L->length--;
    return OK;
}


// 获取List长度
int ListLength(SqList L)
{
    return L.length;
}

// 初始条件：顺序链表已经存在
// 操作结果：对L中的每个元素输出
Status ListTraverse(SqList L)
{
    int i ;
    for(i=1;i<=L.length;i++)
    {
        visit(L.data[i-1]); 
    }
    printf("\n");
    return OK;
}

// 去List A和B的并集
void unionL(SqList* La,SqList* Lb)
{
    int La_len,Lb_len,i;
    ElementType e;
    La_len = La->length;
    Lb_len = Lb->length;

    for(int k = 1;k<=Lb_len;k++)
    {
        GetElem(*Lb,k,&e);
        // 判断e在A中是否存在
        if(!LocateElem(*La,e))
        {
            ListInsert(La,La->length+1,e);
        }
    }
}

int main(int argc, char const *argv[])
{
    SqList L;
    SqList Lb;

    ElementType e;
    Status i;
    int j,k;
    i = InitList(&L);
    printf("初始化L后：L.length=%d\n",L.length);
    for(i = 1;i<=5;i++)
    {
        ListInsert(&L,1,i);
    }
    printf("在L的表头插入1~5后：L.data = ");
    ListTraverse(L);

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);


    i=ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(int i =1;i<=10;i++)
    {
        ListInsert(&L,i,i);
    }
    printf("在L的表尾依次插入1～10后：L.data=\n");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("L.length=%d \n",L.length);

    
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
            i=ListDelete(&L,j,e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L); 

    
    j=5;
    ListDelete(&L,j,e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L); 

	//构造一个有10个数的Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
            i=ListInsert(&Lb,1,j);
    
    printf("Lb:\n");
    ListTraverse(Lb);
    printf("L:\n");
    ListTraverse(L);
	unionL(&L,&Lb);

	printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L); 

    return 0;
}

