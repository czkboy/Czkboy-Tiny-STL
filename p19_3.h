//
//  main.cpp
//  sjjg
//
//  Created by 陈子康 on 2021/6/28.
//

#include <iostream>
#include <vector>
#include "Sqlist_C.h"

using namespace std;


int main19_3(Sqlist &L,Elemtype x) {
    //双指针法删除顺序表为x的元素，要求时间复杂度为O(n)，空间复杂度为O(1)

    // insert code here...
//    vector<int> ve={1,3,2,1,3,3,1};
    int len=L.Length;
    int i=0;
    int j=L.Length-1;
    while (i<=j) {
        if(L.data[i]!=x)
        {
            ++i;
        }
        else
        {
            if (L.data[j]!=x) {
                swap(L.data[i],L.data[j]);
                ++i;
            }
            --j;
        }

    }
    L.Length=i;

    return 0;
}
