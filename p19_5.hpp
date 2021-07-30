//
//  p19_5.h
//  sjjg
//
//  Created by 陈子康 on 2021/7/1.
//

#ifndef p19_5_h
#define p19_5_h
#include "Sqlist_C.h"

void p19_5main(Sqlist &L,int x){
    
    
    int flag=-1,count=0;
    for(int i=0;i<L.Length;++i)
    {
        if (flag==-1) {
            if(L.data[i]==x)
            {
                flag=i;
                ++count;
            }
        }
        else{
            if (L.data[i]==x) {
                ++count;
            }
            else
                L.data[flag++]=L.data[i];
        }
    }
    L.Length-=count;
}


#endif /* p19_5_h */
