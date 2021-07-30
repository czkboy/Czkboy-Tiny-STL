//
//  Sqlist_C.hpp
//  sjjg
//
//  Created by 陈子康 on 2021/6/30.
//

#ifndef Sqlist_h
#define Sqlist_h

#include <stdio.h>
#define MAX 100 //注意, 最后没有分号
typedef int Elemtype;
//线性表的顺序存储
//不可变的,不好用也不继续扩展
struct Sqlist_C{
    int Length;
    Elemtype data[MAX];
};

void SqlistEach(Sqlist_C sqlist){
    for (int i=0; i<sqlist.Length; ++i) {
        printf("%d\n",sqlist.data[i]);
    }
    printf("\n");
}



#endif /* Sqlist_h */
