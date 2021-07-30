//
//  BinTree.h
//  MYSTL
//
//  Created by K on 2020/11/3.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef BinTree_h
#define BinTree_h

#define MAXNODE 100
#include <stdio.h>
#include <stdlib.h>
typedef char value_type;


typedef struct _BinTree_node{
    struct _BinTree_node* right;
    struct _BinTree_node* left;
    value_type data;
}BinTree_node,*BinTree_prt;



void createBiTree_by_str(BinTree_node **T){
    value_type ch=0;
    if((ch = getchar()) == '#'){
        *T=NULL;
    }else{
        *T=(BinTree_node *)malloc(sizeof(BinTree_node));
        (*T)->data = ch;
        createBiTree_by_str(&(*T)->left);
        createBiTree_by_str(&(*T)->right);

    }
}


void pre_foreach(BinTree_prt T){
    if(T){
        printf("%c",T->data);
        pre_foreach(T->left);
        pre_foreach(T->right);
    }

}

void middle_foreach(BinTree_prt T){
    
    if(T){
        middle_foreach(T->left);
        printf("%c",T->data);
        middle_foreach(T->right);
    }

}

void end_foreach(BinTree_prt T){
    
    if(T){
        end_foreach(T->left);
        end_foreach(T->right);
        printf("%c",T->data);
    }

}

int Bintree_deep(BinTree_prt T,int count){
    int right=0,left=0;
    if(T){
        left=Bintree_deep(T->left,count+1);
        right=Bintree_deep(T->right,count+1);
        
    }
    else
    {
        return count;
    }
    return left>right?left:right;
}


int leafCount(BinTree_prt T){
    int lnum=0,rnum=0;
    if(T == NULL){
        return 0;
    
    }else if(T->left == NULL && T->right == NULL){
        return 1;
    }else{
        lnum = leafCount(T->left);
        rnum = leafCount(T->right);
        return lnum+rnum;
    }
}

int countTree(BinTree_prt T){
    int lnum,rnum;
        if(T == NULL){
        return 0;
    
        }else{
            lnum = countTree(T->left);
            rnum = countTree(T->right);
            return lnum + rnum + 1;
        }

}

void level_foreach(BinTree_prt T){
    BinTree_prt queue[100];
//队列最大为100默认
    int front=0;
    int rear=0;
    if(T!=NULL)
    {
        queue[rear]=T;
        rear++;
        
    }
    else
        return;
    while (front!=rear) {
        BinTree_prt itor = queue[front];
        front=(front+1)%MAXNODE;
        printf("%c",itor->data);
        if(itor->left!=NULL)
        {
            if ((rear + 1) % MAXNODE == front)
            {
                return ;
            }
            queue[rear]=itor->left;
            rear=(rear+1)%MAXNODE;
        }
        if(itor->right!=NULL)
        {
            if ((rear + 1) % MAXNODE == front)
            {
                return ;
            }
            queue[rear]=itor->right;
            rear=(rear+1)%MAXNODE;
        }
        
        
    }
        
}

#endif /* BinTree_h */
