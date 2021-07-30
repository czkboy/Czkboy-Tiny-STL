//
//  p19_4.h
//  sjjg
//
//  Created by 陈子康 on 2021/6/30.
//

#ifndef p19_4_h
#define p19_4_h

#include <iostream>
#include "Sqlist_C.h"

bool mainp19_4(Sqlist &L,int s,int t){
    //删除s到t的元素
    int k=0,i=0;
    if(s>=t||L.Length==0)
    {
        std::cout<<"p19_4 输入 False"<<std::endl;
        return false;
    }
    else
    {
        
        for(;k<L.Length;k++)
        {
            
            if(L.data[k]<=s||L.data[k]>=t){
                L.data[i]=L.data[k];
                ++i;
            }//牛啊,短短两行代码就实现了,快慢指针,相当于吧可以的数据复制到另外一个数组,这里只是复制到原本数组而已
                
            
        }
    }
    L.Length=i;
    return true;
};


#endif /* p19_4_h */
