//
//  BSTree.h
//  MYSTL
//
//  Created by K on 2020/12/7.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef BSTree_h
#define BSTree_h

#include <stdio.h>

#define ngx_rbt_black(node) ((node)->color = 0)

#define ngx_rbtree_sentinel_init(node)  ngx_rbt_black(node)

#define BStree_init(tree, s, i) \
    BStree_sentinel_init(s); \
    (tree)->root = s; \
    (tree)->sentinel = s;(tree)->insert =i \


typedef unsigned int BStree_key_t;
typedef int BStree_key_int_t;
typedef struct BStree_node_s BStree_node_t;
//表示结点,以后用来插入用的。

struct BStree_node_s {
    BStree_key_t key; //unsigned int 无符号整形来定义 key关键字
    BStree_node_t *left; //指向左孩子节点
    BStree_node_t *right; //指向右孩子结点
};



typedef struct BStree_s BStree_t; //“_s”是结构体“_t”是类型
//下面是一个函数指针变量类型的定义，是红黑树插入函数的指针
//参数有树根结点、插入结点和哨兵结点的指针



//插入函数指针。可以调用BStree_insert_value(作用是找到合适的 插入点)
typedef void (*BStree_insert_pt) (BStree_node_t *root,
                                  BStree_node_t *node,BStree_node_t *sentinel); //函数指针里面的参数有 根节点、插入结点、哨兵结点的指针


struct BStree_s { //
    BStree_node_t *root; //根节点指针
    BStree_node_t *sentinel; //哨兵结点指针
    BStree_insert_pt insert; //插入函数指针
};






void BStree_insert(BStree_t *tree, BStree_node_t *node); //插入




BStree_node_t *BStree_next(BStree_t *tree,BStree_node_t *node);




#endif /* BSTree_h */
