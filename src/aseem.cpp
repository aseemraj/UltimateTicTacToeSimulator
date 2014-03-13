#include <iostream>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
using namespace std;

int me, prev, tomove=0;
int b[10][10];

int self(int box)
{
    switch(box)
    {
        case 1:
            return 1;
        case 2:
            return 5;
        case 3:
            return 9;
        case 4:
            return 37;
        case 5:
            return 41;
        case 6:
            return 45;
        case 7:
            return 73;
        case 8:
            return 77;
        case 9:
            return 81;

    }
}
int position(int i, int j)
{
    return (9*(i-1) + j);
}
int cellx(int pos)
{
    return (pos-1)/9 + 1;
}
int celly(int pos)
{
    if(pos%9==0)
        return 9;
    return pos%9;
}

int directedbox(int pos)
{
    int i = cellx(pos);
    int j = celly(pos);
    if(i%3==1)
    {
        if(j%3==1)
            return 1;
        if(j%3==2)
            return 2;
        if(j%3==0)
            return 3;
    }
    else if(i%3==2)
    {
        if(j%3==1)
            return 4;
        if(j%3==2)
            return 5;
        if(j%3==0)
            return 6;
    }
    if(i%3==0)
    {
        if(j%3==1)
            return 7;
        if(j%3==2)
            return 8;
        if(j%3==0)
            return 9;
    }
}

int getbox(int pos)
{
    int i = cellx(pos);
    int j = celly(pos);
    if(i>0 and i<4 and j>0 and j<4)
        return 1;
    else if(i>3 and i<7 and j>0 and j<4)
        return 4;
    else if(i>6 and i<10 and j>0 and j<4)
        return 7;
    else if(i>0 and i<4 and j>3 and j<7)
        return 2;
    else if(i>3 and i<7 and j>3 and j<7)
        return 5;
    else if(i>6 and i<10 and j>3 and j<7)
        return 8;
    else if(i>0 and i<4 and j>6 and j<10)
        return 3;
    else if(i>3 and i<7 and j>6 and j<10)
        return 6;
    else if(i>6 and i<10 and j>6 and j<10)
        return 9;
}
int geti(int box)        //Get row of topleft cell of box
{
    int i;
    switch(int((box-1)/3))
    {
        case 0:
            i=1;
            break;
        case 1:
            i=4;
            break;
        case 2:
            i=7;
            break;
    }
    return i;
}
int getj(int box)        //Get column of topleft cell of box
{
    int j;
    switch(box%3)
    {
        case 0:
            j=7;
            break;
        case 1:
            j=1;
            break;
        case 2:
            j=4;
            break;
    }
    return j;
}

bool check_box_full(int box)
{
    int i,j;
    i = geti(box);
    j = getj(box);
    int row, col;
    for(row=i;row<i+3;row++)
        for(col=j;col<j+3;col++)
            if(b[row][col]==0)
                return false;
    return true;
}

void direct_to_center()
{
    int box;
    switch(int(prev/9))
    {
        case 3:
            if(prev%3==0)
                box = 3;
            else
                box = prev%3;
            break;
        case 4:
            if(prev%3==0)
                box = 6;
            else
                box = 3 + prev%3;
            break;
        case 5:
            if(prev%3==0)
                box = 9;
            else
                box = 6 + prev%3;
            break;
    }
    if(!check_box_full(5))
    {
        int startr = geti(box);
        int startc = getj(box);
        tomove = position(startr+1, startc+1);
    }
    else
    {
        tomove = self(box);
    }
}

void trapped()
{
    int i, j;
    int box = directedbox(prev);
    if(check_box_full(box))
    {
        for(i=1;i<10;i++)
        {
            for(j=1;j<10;j++)
            {
                if(b[cellx(self(getbox(position(i, j))))][celly(self(getbox(position(i, j))))]==0)
                {
                    tomove = self(getbox(position(i, j)));
                    return;
                }
            }
        }
    }
    else
    {
        if(b[cellx(self(box))][celly(self(box))]==0)
            tomove = self(box);
        else
        {
            for(i=geti(box);i<geti(box)+3;i++)
            {
                for(j=getj(box);j<getj(box)+3;j++)
                {
                    if(b[i][j]==0)
                    {
                        tomove = position(i, j);
                        return;
                    }
                }
            }
        }
    }
}
void trap()
{
    int box_to_direct = getbox(prev);
    int i, j;
    int boxx = geti(directedbox(prev));
    int boxy = getj(directedbox(prev));
    if(!check_box_full(box_to_direct))
    {
        int box;
        bool i_have_choice = check_box_full(directedbox(prev));
        if(i_have_choice)
        {
            switch(getbox(prev))
            {
                case 1:
                    box = 9;
                    box_to_direct = check_box_full(1)?9:1; break;
                case 2:
                    box = 8; break;
                    box_to_direct = check_box_full(1)?8:2; break;
                case 3:
                    box = 7; break;
                    box_to_direct = check_box_full(1)?7:3; break;
                case 4:
                    box = 6; break;
                    box_to_direct = check_box_full(1)?6:4; break;
                case 6:
                    box = 4; break;
                    box_to_direct = check_box_full(1)?4:6; break;
                case 7:
                    box = 3; break;
                    box_to_direct = check_box_full(1)?3:7; break;
                case 8:
                    box = 2; break;
                    box_to_direct = check_box_full(1)?2:8; break;
                case 9:
                    box = 1; break;
                    box_to_direct = check_box_full(1)?1:9; break;
            }
            boxx = geti(box);
            boxy = getj(box);
            for(int it1=boxx;it1<boxx+3;it1++)
            {
                for(int it2=boxy;it2<boxy+3;it2++)
                {
                    if(directedbox(position(boxx, boxy))==box_to_direct)
                    {
                        tomove = position(boxx, boxy);
                        return;
                    }
                }
            }
        }
        else
        {
            switch(box_to_direct)
            {
                case 1:
                    i = boxx; j = boxy;
                    break;
                case 2:
                    i = boxx; j = boxy+1;
                    break;
                case 3:
                    i = boxx; j = boxy+2;
                    break;
                case 4:
                    i = boxx+1; j = boxy;
                    break;
                case 6:
                    i = boxx+1; j = boxy+2;
                    break;
                case 7:
                    i = boxx+2; j = boxy;
                    break;
                case 8:
                    i = boxx+2; j = boxy+1;
                    break;
                case 9:
                    i = boxx+2; j = boxy+2;
                    break;
            }
            if(b[i][j]==0)
            {
                tomove = position(i, j);
                return;
            }
            else
            {
                box_to_direct = getbox(position(i, j));
                tomove = self(box_to_direct);
                return;
            }
        }
    }
    else
    {
        if(b[cellx(self(directedbox(prev)))][celly(self(directedbox(prev)))]==0)
            tomove = self(directedbox(prev));
        else
        {
            for(int it=1;it<=81;it++)
            {
                if(!check_box_full(getbox(it)) and b[cellx(it)][celly(it)]==2)
                {
                    i = geti(directedbox(prev));
                    j = getj(directedbox(prev));
                    box_to_direct = getbox(it);
                    for(int row=i;row<i+3;row++)
                    {
                        for(int col=j;col<j+3;col++)
                        {
                            if(directedbox(position(row, col))==box_to_direct)
                            {
                                tomove = position(row, col);
                                return;
                            }
                        }
                    }
                }

            }
        }
    }
}
void manmohan_singh()
{
    int box = directedbox(prev);
    int i, j;
    bool choice_again = check_box_full(box);
    if(choice_again)
    {
        for(int boxit=1;boxit<=9;boxit++)
        {
            if(!check_box_full(boxit))
            {
                for(i=geti(boxit);i<geti(boxit)+3;i++)
                {
                    for(j=getj(boxit);j<getj(boxit)+3;j++)
                    {
                        if(b[i][j]==0)
                        {
                            tomove=position(i, j);
                            return;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(i=geti(box);i<geti(box)+3;i++)
            for(j=getj(box);j<getj(box)+3;j++)
                if(b[i][j]==0)
                    tomove=position(i, j);
    }
}
int main()
{
    FILE *fp;
    fp=fopen("boardFile","r");
    int i,j,cnt=0;
    char c[4];
    for(i=1;i<10;i++)
    {
        for(j=1;j<9;j++)
        {
            fgets(c,3,fp);
            b[i][j]=c[0]-48;
        }
        fgets(c, 4, fp);
        b[i][j]=c[0]-48;
    }
    fgets(c, 3, fp);
    me = c[0]-48;
    fgets(c, 3, fp);
    if(c[1]>=48 and c[1]<=57)
        prev = (c[0]-48)*10 + c[1]-48;
    else
        prev = c[0]-48;


    if(prev == 0)
        tomove = 41;
    else
    {
        if(me==1)
        {
            if(prev==31 or prev==32 or prev==33 or prev==40 or prev==42 or prev==49 or prev==50 or prev==51)
                direct_to_center();
            else
                trap();
        }
        else
        {
            trapped();
        }
    }
    if(b[cellx(tomove)][celly(tomove)]==0 && tomove!=0)
        cout<<tomove;
    else
    {
        manmohan_singh();
        cout<<tomove;
    }
    return 0;
}
