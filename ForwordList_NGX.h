//
//  My_ngx_forword_list.h
//  MYSTL
//
//  Created by K on 2020/12/26.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef My_ngx_forword_list_h
#define My_ngx_forword_list_h

#define STRMAX 10

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _List_node
{

    struct _List_node *pre;
    void *data;
    unsigned ndata;
    
}FList_node,*Link_list;

typedef struct _Forward_List
{

    FList_node  *last;        /* 指向最新的链表节点*/
    FList_node   *part;        /* 第一个链表节点*/
    size_t            size;        /* 这个链表默认的每个元素大小 */
    unsigned        nalloc;            /* 每个节点part 可以支持多少个元素*/
    
}Forward_List;

Forward_List *
Flist_create( int n, size_t size)
{
    Forward_List  *list;
 
    /* 从内存池上面分配一块内存，存储ngx_list_t数据结构 */
    list = (Forward_List*)malloc(sizeof(Forward_List));
    if (list == NULL) {
        return NULL;
    }
 
    /* ngx的头结点和list写在一起？*/
    list->part = (FList_node*)malloc(sizeof(FList_node));
    if (list->part == NULL) {
        return NULL;
    }
    
    
    /* 分配一个链表节点的内存块。内存大小  n * size*/
    list->part->data = malloc( n * size);
    if (list->part->data == NULL) {
        return NULL;
    }
 
    list->part->ndata = 0;         /* 使用的元素个数    */
    list->part->pre = NULL;     /* 下一个节点        */
    list->last = list->part;     /* 最后一个节点地址     */
    list->size = size;          /* 每个元素的大小    */
    list->nalloc = n;            /* 分配多少个         */
 
    return list;
}


void *
Flist_push_back(Forward_List*l)
{
    void             *elt;
    FList_node  *last;

    last = l->last;

    if (last->ndata ==l->nalloc) {  //链表数据区满

        /* the last part is full, allocate anew list part */

        last =(FList_node  *)malloc( sizeof(FList_node));  //分配节点(list part)
        if (last == NULL) {
            return NULL;
        }

        last->data =malloc( l->nalloc * l->size);//分配该节点(part)的数据区
        if (last->data == NULL) {
            return NULL;
        }

        last->ndata = 0;
        last->pre = NULL;

        l->last->pre =last;  //将分配的list part插入链表
        l->last = last;        //并修改list头的last指针
    }

   //last->elts为首地址
    elt = (char *)last->data + l->size * last->ndata; //计算下一个数据在链表数据区中的位置,ndata当前数量
    last->ndata++;  //实际存放的数据个数加1

    return elt;  //返回该位置
}


void* Flist_getpart(Forward_List*l)
{
    return l->part->data;
}

void* Flist_getlast(Forward_List*l)
{
    if(l->last->ndata!=0)
    {}
    else
    {
        FList_node  *i=l->part;
        while (i->pre==l->last) {
            i=i->pre;
        }
        l->last=i;
        
    }
    int flag=l->last->ndata;
    --flag;
    return (char *)l->last->data + l->size * l->last->ndata;
}





void deallocate_node(void *l)
{
    if (l!=NULL)
        free(l);
}

void Flist_pop_back_aux(Forward_List*l)
{
    
    deallocate_node(l->last->data);
    
    FList_node  *i=l->part;
    while (i->pre==l->last) {
        i=i->pre;
    }
    deallocate_node(l->last);
    i->pre=NULL;
    l->last=i;
    l->last->ndata--;
    
}

void Flist_pop_back(Forward_List*l)
{
    if(l->last->ndata!=0)
    {
        
        l->last->ndata--;
        
        
    }
    else
    {
        Flist_pop_back_aux(l);
    }
    
}

void Flist_clear(Forward_List*l)
{
    FList_node  *i=l->part;
    FList_node  *j=i;
    while (i!=NULL) {
        
        deallocate_node(i->data);
        i->data=NULL;//需要吗
        i=i->pre;
    }
    
    while(j)
    {
        i=j->pre;
        deallocate_node(j);
        j=i;
    }
    
    deallocate_node(l);
}
/**
 * 创建链表
 */



#endif /* My_ngx_forword_list_h */
