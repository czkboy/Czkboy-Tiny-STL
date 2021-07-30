//
//  CForward_list.h
//  MYSTL
//
//  Created by K on 2020/9/23.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef CForward_list_h
#define CForward_list_h

#define STRMAX 10

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct _List_node
{

    struct _List_node *pre;
    char data;
    
}_List_node,*Link_list;




_List_node* Create( int k)
{
    Link_list list=(Link_list)malloc(sizeof(_List_node));
    list->data=0;
    list->pre=NULL;
    _List_node* pre_node=NULL;
    for(int i=1;i<=k;++i)
    {
        char d=0;
        printf("请输入第%d个字符：",i);
        
        scanf("%c",&d);
        fflush(stdin);//为了不读入换行，刷新缓存区

        _List_node* node=(_List_node*)malloc(sizeof(_List_node));
        node->data=d;
        node->pre=pre_node;
        pre_node=node;//不一样的头插法~，最后才改变头结点的指针
    }
    list->pre=pre_node;
    
    
    return list;
};

void For_each(Link_list list)
{
    _List_node *node=list;
    while ((node=node->pre)!=NULL) {
        printf("%c",node->data);
    }
    printf("\n");
};



_List_node* _reverse(_List_node* head)
{
    if(head==NULL||head->pre==NULL)
        return head;
    _List_node *newhead = _reverse(head->pre);
    head->pre->pre=head;
    head->pre=NULL;
    return newhead;
};

void Reverse(Link_list list)
{
    list->pre=_reverse(list->pre);
}



void Remove(Link_list head,char val)
{
    while (head->pre->data!=val) {
        head=head->pre;
    }
    _List_node* it=head->pre;
    head->pre=head->pre->pre;//有没有可能找不到head->pre->pre，长度不够
    free(it);
}

void Insert(_List_node *head,char val)
{
    _List_node* node = (_List_node*)malloc(sizeof(_List_node));
    node->data=val;
    node->pre=head->pre;
    head->pre=node;
    
}



#endif /* CForward_list_h */
