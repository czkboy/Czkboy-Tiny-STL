//
//  main.cpp
//  mystl2
//
//  Created by K on 2021/1/1.
//  Copyright © 2021 K. All rights reserved.
//



//Maze.c
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include"My_ngx_forward_list.hpp"
#include"Maze.hpp"
//初始化迷宫

void myprint(char *str,int i=2,char c=' '){
    size_t len=strlen(str);
    if (len<i)
    {
        printf("%s",str);
        int flag=int(i-len);
        while (--flag) {
            printf("%c",c);
        }
        
    }
    else
        printf("%s",str);
}


typedef Position SDataType;

void InitMaze(Maze *m,int c,int r )
{
    int i, j,count=0;
    if (NULL == m)
    {
        return;
    }
    for (i = 0; i < c; i++)
    {
        for (j = 0; j < r; j++)
        {
            if(i==0||j==0||i==c-1||j==r-1)

                m->_map[i][j] =    1;
            else if(count>0)
            {
                m->_map[i][j] = 0;
                --count;
            }
            else
            {
                m->_map[i][j] = rand() % 2;
                if (m->_map[i][j] == 1)
                {
                    count=rand() % 3;
                }
            }
        }
    }
}


//判断入口是否合法
int IsValidEntry(Maze *m, Position entry,int c,int r)
{
    assert(m);    //保证迷宫存在
    if (0 != entry._x || entry._x != c-1 || 0 != entry._y || entry._y != r-1)   //在边界
    {
        return 0 == m->_map[entry._x][entry._y];     //如果存的是0，表示是通路；否则，不是通路
    }
    return 0;    //不在边界则一定不是合法入口
}


//判断是否是通路
int IsPass(Maze *m, Position cur)
{   //cur一定在迷宫中
    if (0 == m->_map[cur._x][cur._y])  //若cur步存的是0，则表示是通路
    {
        return 1;
    }
    return 0;
}


//判断是否是出口
int IsExit(Maze *m, Position cur, Position entry,int x,int y)
{
    /*if (cur._x == entry._x && cur._y == entry._y)
    {
        return 0;
    }*/
    if (cur._x == x && y == cur._y )
    {
        return 1;
    }
    return 0;
}


//entry表示迷宫的入口，栈s保存走过的路径
void PassMaze(Maze *m, Position entry, Forward_List *s,int x1,int y1,int x2,int y2,int c,int r)
{
    Position cur, next;
    //先判断入口是否合法，不合法直接退出
    if (!IsValidEntry(m, entry,c,r))
    {
        printf("非法的迷宫入口!\n");
        return;
    }

    Position* p= (Position*)Flist_push_back(s);    //入口合法，让其入栈
    *p = entry;
    while (!Flist_empty(s))    //栈不为空，表明有出口。若迷宫没有入口，则cur会一直出栈，直到空
    {
        cur = *(Position*)Flist_getlast(s);  //取栈顶（前提：栈不为空）
        m->_map[cur._x][cur._y] = 2; //标记一下，代表此位置已经走过

        if (IsExit(m, cur, entry,x2,y2))     //检测cur是否是出口，若为出口，直接返回退出
        {
            return;
        }

        //上
        next = cur;
        next._x -= 1;
        if (IsPass(m, next))
        {
                //下一步可以走通，让其入栈，先保存起来
            Position* p = (Position*)Flist_push_back(s);
            *p = next;
            continue;

        }

        //左
        next = cur;
        next._y -= 1;
        if (IsPass(m, next))
        {
            Position* p = (Position*)Flist_push_back(s);
            *p = next;
               //下一步可以走通，让其入栈，先保存起来
            continue;

        }

        //右
        next = cur;
        next._y += 1;
        if (IsPass(m, next))
        {
            Position* p = (Position*)Flist_push_back(s);
            *p = next;
            //下一步可以走通，让其入栈，先保存起来
            continue;

        }

        //下
        next = cur;
        next._x += 1;
        if (IsPass(m, next))
        {
            Position* p = (Position*)Flist_push_back(s);
            *p = next;
            //下一步可以走通，让其入栈，先保存起来
            continue;
        }

        Flist_pop_back(s);     //上下左右均走不通，表明cur步走错了，让其出栈，不要出现在最终路径中
        m->_map[cur._x][cur._y] = 3;     //标记走错的步为3
    }

}


//打印迷宫
void PrintMaze(Maze *m,int c,int r)
{
    int i, j;
    if (NULL == m)
    {
        return;
    }
    printf("  ");
    for (j = 0; j < r; j++)
    {
        printf("%-2d", j);
    }
    printf("\n");
    for (i = 0; i < c; i++)
    {
        printf("%-2d",i);
        for (j = 0; j < r; j++)
        {
            if(m->_map[i][j]==1)
                myprint(" ■");
            else if (m->_map[i][j] == 2)
                myprint(" ☆");
            else
                myprint(" □");
        }
        printf("\n");
    }
}


//打印最终路径
void Print(Forward_List *s)
{
    
    FList_node *part;
    Position *data;
    Position next;
    int flag = 0;
    for (part = s->part; part; part = part->pre)
    {
        data = (Position *)part->data;
        int k = 0;
        for (int i = 0; i < part->ndata; ++i)
        {
            if (i + 1 >= part->ndata)
            {
                if(part->pre)
                    next = *(Position *)(part->pre->data);
            }
            else
                next = data[i + 1];
            if (data[i]._x - next._x == 1&& data[i]._y - next._y == 0)
                k = 4;
            else if (data[i]._x - next._x == -1&& data[i]._y - next._y == 0)
                k = 3;
            else if (data[i]._x - next._x == 0&& data[i]._y - next._y == 1)
                k = 2;
            else if (data[i]._x - next._x == 0&& data[i]._y - next._y == -1)
                k = 1;
            if(flag!=0)
                printf(" -> ");
            printf("(%d,%d,%d) ", data[i], k);
            flag = 1;
            
        }
    }
}




void DFS()
{
    printf("输入迷宫大小x与y用空格隔开如3 3\n");
    int c, r;
    scanf("%d %d", &c, &r);

    
    
    Forward_List *s = Flist_create(1, sizeof(Position));
    Position entry;
    Maze m;
    InitMaze(&m, c, r);
    PrintMaze(&m, c, r);
    printf("\n");

    printf("自动生成迷宫■为障碍，□为通路，☆为路径,请输入起点和终点用空格隔开如 2 2 3 1\n");
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    printf("--------------------------------\n");

    entry._x = x1;
    entry._y = y1;
    PassMaze(&m, entry, s,x1,y1,x2,y2,c,r);

    if (Flist_empty(s)){
        printf("-1(无通路)");
        return;
    }
        
    PrintMaze(&m,c,r);
    printf("\n");
    Print(s);

}

int main()
//main 函数
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    DFS();
}
