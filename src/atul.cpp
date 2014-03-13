#include<iostream>
#include<string.h>
#include<sstream>
#include<cstring>
#include<fstream>

using namespace std;
int a[83];
int my_move;
int enemy_move;
int B=0;
int boxes[9];
int small_box_count[9] = {0,0,0,0,0,0,0,0,0};
int push;
int box_is_full[9] = {0,0,0,0,0,0,0,0,0};   //box_full = 1
int count_full_boxes = 0;
int who_wins_box[9];                        //0- no winner //1- I win //2- Enemy wins
int count_enemy_boxes = 0;


void get_array()
{
    string input_user;
    ifstream file2;
    file2.open("boardFile", ios::in);
    int i=0;
    while(!file2.eof())
    {
        getline(file2, input_user);
        istringstream iss(input_user);
        int cnt =0;
        while(iss)
        {
            string sub;
            iss >> sub;
            istringstream buf(sub.substr(0,10));
            if((cnt+1)%10!=0)
                buf >> a[i++];
            cnt++;
        }
    }
    my_move = a[81];
    if(my_move == 1)
        enemy_move = 2;
    else
        enemy_move = 1;
    file2.close();
}


void read_push()
{
    string input_user;
    ifstream file3;
    file3.open("push", ios::in);
    int i=0;
    while(!file3.eof())
    {
        getline(file3, input_user);
        istringstream iss(input_user);
        int cnt =0;
        while(iss)
        {
            string sub;
            iss >> sub;
            istringstream buf(sub.substr(0,10));
            if((cnt+1)%10!=0)
                buf >> push;
            cnt++;
        }
    }
    file3.close();
}

void print_board()
{
    for(int i=0;i<83;i++)
    {
        cout<<a[i];
        if((i+1)%9==0)
            cout<<endl;
        else
            cout<<" ";
    }
}

void active_mini_board()
{
    if(a[82] == 0)
    {
        B = 4;
        push = 4;
        return;
    }
    if((a[82]>=1&&a[82]<=9)||(a[82]>=28&&a[82]<=36)||(a[82]>=55&&a[82]<=63))
    {
        B = a[82]%3;
        if(a[82]%3==0)
            B=3;
    }
    else if((a[82]>=10&&a[82]<=18)||(a[82]>=37&&a[82]<=45)||(a[82]>=64&&a[82]<=72))
    {
        B = (a[82]%3)+3;
        if(a[82]%3==0)
            B=6;
    }
    else
    {
        B = (a[82]%3)+6;
        if(a[82]%3==0)
            B=9;
    }
    return;
}

void create_file_for_push()
{
    ofstream file1;
    file1.open("push", ios::out);
    file1<<push;
}

void make_mini_board(int checker)
{
    switch(checker)
    {
        case 1: for(int i=0,j=0; i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 2: for(int i=0, j=3;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 3: for(int i=0, j=6;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 4: for(int i=0, j=27;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 5: for(int i=0, j=30;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 6: for(int i=0, j=33;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 7: for(int i=0, j=54;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 8: for(int i=0, j=57;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
                break;
        case 9: for(int i=0, j=60;i<=8; i+=3,j+=9)
                {
                    boxes[i] = j;
                    boxes[i+1] = j+1;
                    boxes[i+2] = j+2;
                }
    }
    return;
}


void is_full()
{
    for(int i=0; i<9; i++)
    {
        int cnt = 0;
        make_mini_board(i);
        for(int j=0; j<9; j++)
        {
            if(a[boxes[j]] != 0)
                cnt++;
        }
        if(cnt==9)
        {
             box_is_full[i] = 1;
             count_full_boxes++;
        }
    }
    return;
}


void analyze_winner()
{
    for(int i=0; i<=9; i++)
    {
        make_mini_board(i);
        if(a[boxes[0]]==my_move&&a[boxes[1]]==my_move&&a[boxes[2]]==my_move
            ||a[boxes[3]]==my_move&&a[boxes[4]]==my_move&&a[boxes[5]]==my_move
            ||a[boxes[6]]==my_move&&a[boxes[7]]==my_move&&a[boxes[8]]==my_move
            ||a[boxes[0]]==my_move&&a[boxes[3]]==my_move&&a[boxes[6]]==my_move
            ||a[boxes[1]]==my_move&&a[boxes[4]]==my_move&&a[boxes[7]]==my_move
            ||a[boxes[2]]==my_move&&a[boxes[5]]==my_move&&a[boxes[8]]==my_move
            ||a[boxes[0]]==my_move&&a[boxes[4]]==my_move&&a[boxes[8]]==my_move
            ||a[boxes[2]]==my_move&&a[boxes[6]]==my_move&&a[boxes[6]]==my_move)
                who_wins_box[i]=1;

        else if(a[boxes[0]]==enemy_move&&a[boxes[1]]==enemy_move&&a[boxes[2]]==enemy_move
            ||a[boxes[3]]==enemy_move&&a[boxes[4]]==enemy_move&&a[boxes[5]]==enemy_move
            ||a[boxes[6]]==enemy_move&&a[boxes[7]]==enemy_move&&a[boxes[8]]==enemy_move
            ||a[boxes[0]]==enemy_move&&a[boxes[3]]==enemy_move&&a[boxes[6]]==enemy_move
            ||a[boxes[1]]==enemy_move&&a[boxes[4]]==enemy_move&&a[boxes[7]]==enemy_move
            ||a[boxes[2]]==enemy_move&&a[boxes[5]]==enemy_move&&a[boxes[8]]==enemy_move
            ||a[boxes[0]]==enemy_move&&a[boxes[4]]==enemy_move&&a[boxes[8]]==enemy_move
            ||a[boxes[2]]==enemy_move&&a[boxes[6]]==enemy_move&&a[boxes[6]]==enemy_move)
             {
                 who_wins_box[i]=2;
                 count_enemy_boxes++;
             }

        else
            who_wins_box[i]=0;
    }
}

void count_small_boxes()
{
    int p;
    for(int i=0; i<9; i++)
    {
        if(i == 0) p = 0;
        else if(i == 1) p = 1;
        else if(i == 2) p = 2;
        else if(i == 3) p = 9;
        else if(i == 4) p = 10;
        else if(i == 5) p = 11;
        else if(i == 6) p = 18;
        else if(i == 7) p = 19;
        else p = 20;

        if(a[p] != 0) small_box_count[i]++;
        if(a[p+3] != 0) small_box_count[i]++;
        if(a[p+6] != 0) small_box_count[i]++;
        if(a[p+27] != 0) small_box_count[i]++;
        if(a[p+30] != 0) small_box_count[i]++;
        if(a[p+33] != 0) small_box_count[i]++;
        if(a[p+54] != 0) small_box_count[i]++;
        if(a[p+57] != 0) small_box_count[i]++;
        if(a[p+60] != 0) small_box_count[i]++;
    }
}

void check_my_win()
{
    //if any center move is vacant
    if(boxes[0]==my_move&&boxes[2]==my_move&&boxes[1]==0)
    { push = 1; a[boxes[1]] = my_move;}
    else if(boxes[0]==my_move&&boxes[6]==my_move&&boxes[3]==0)
    { push = 3; a[boxes[3]] = my_move;}
    else if(boxes[0]==my_move&&boxes[8]==my_move&&boxes[4]==0)
    { push = 4; a[boxes[4]] = my_move;}
    else if(boxes[1]==my_move&&boxes[7]==my_move&&boxes[7]==0)
    { push = 4; a[boxes[4]] = my_move;}
    else if(boxes[2]==my_move&&boxes[8]==my_move&&boxes[5]==0)
    { push = 5; a[boxes[5]] = my_move;}
    else if(boxes[2]==my_move&&boxes[6]==my_move&&boxes[4]==0)
    { push = 4; a[boxes[4]] = my_move;}
    else if(boxes[3]==my_move&&boxes[5]==my_move&&boxes[4]==0)
    { push = 4; a[boxes[4]] = my_move;}
    else if(boxes[6]==my_move&&boxes[8]==my_move&&boxes[7]==0)
    { push = 7; a[boxes[7]] = my_move;}

    //if any side box is vacant, horizontally
    if(boxes[0]==my_move&&boxes[1]==my_move&&boxes[2]==0)
    { push = 2; a[boxes[2]] = my_move;}
    else if(boxes[1]==my_move&&boxes[2]==my_move&&boxes[0]==0)
    { push = 0; a[boxes[0]] = my_move;}
    else if(boxes[3]==my_move&&boxes[4]==my_move&&boxes[5]==0)
    { push = 5; a[boxes[5]] = my_move;}
    else if(boxes[4]==my_move&&boxes[5]==my_move&&boxes[3]==0)
    { push = 3; a[boxes[3]] = my_move;}
    else if(boxes[6]==my_move&&boxes[7]==my_move&&boxes[8]==0)
    { push = 8; a[boxes[8]] = my_move;}
    else if(boxes[7]==my_move&&boxes[8]==my_move&&boxes[6]==0)
    { push = 6; a[boxes[6]] = my_move;}

    //if any side box is vacant, vertically
    if(boxes[0]==my_move&&boxes[3]==my_move&&boxes[6]==0)
    { push = 6; a[boxes[6]] = my_move;}
    else if(boxes[3]==my_move&&boxes[6]==my_move&&boxes[0]==0)
    { push = 0; a[boxes[0]] = my_move;}
    else if(boxes[1]==my_move&&boxes[4]==my_move&&boxes[7]==0)
    { push = 7; a[boxes[7]] = my_move;}
    else if(boxes[4]==my_move&&boxes[7]==my_move&&boxes[1]==0)
    { push = 1; a[boxes[1]] = my_move;}
    else if(boxes[2]==my_move&&boxes[5]==my_move&&boxes[8]==0)
    { push = 8; a[boxes[8]] = my_move;}
    else if(boxes[5]==my_move&&boxes[8]==my_move&&boxes[2]==0)
    { push = 2; a[boxes[2]] = my_move;}

    //if any side box is vacant, diagonally
    if(boxes[0]==my_move&&boxes[4]==my_move&&boxes[8]==0)
    { push = 8; a[boxes[8]] = my_move;}
    else if(boxes[4]==my_move&&boxes[8]==my_move&&boxes[0]==0)
    { push = 0; a[boxes[0]] = my_move;}
    else if(boxes[2]==my_move&&boxes[4]==my_move&&boxes[6]==0)
    { push = 6; a[boxes[6]] = my_move;}
    else if(boxes[4]==my_move&&boxes[6]==my_move&&boxes[2]==0)
    { push = 2; a[boxes[2]] = my_move;}



}

void reinit_push()
{
    for(int i = 0; i<9 ; i++)       //start pushing in the opposite block now... Second level of pushing...
        if(box_is_full[i]==1)
            push = 8 - i + 1;

    if(box_is_full[push]==1)        //if opposite is full, move to the center of the board... Third level of pushing...
        push = 5;

    if(count_enemy_boxes >=2)
        check_my_win();
    return;
}


void dabao_strategy()
{
    count_small_boxes();
    if(box_is_full[B]==1)
    {
        //you have a free chance... think of the algo.....
        reinit_push();
    }
    if(small_box_count[push-1]< 8 - count_full_boxes)
     {
         cout<<endl<<small_box_count[push-1]<<"\tNew push = "<<push<<endl;
         a[boxes[push-1]] = my_move;
     }
     else
     {
         push = B;
         cout<<small_box_count[push-1]<<endl;
         cout<<"New push is here : "<<push<<endl;
         a[boxes[push-1]] = my_move;
     }
}




void find_move_mini_board()
{
    dabao_strategy();
}





int main()
{
    get_array();
    read_push();
    //print_board();
    active_mini_board();
    make_mini_board(B);
    find_move_mini_board();

    is_full();
    for(int i=0; i<9; i++)
        if(box_is_full[i]==1)
            cout<<"\n"<<i<<" is Full";

    analyze_winner();
    for(int i=0; i<9; i++)
        if(who_wins_box[i]==1)
            cout<<"\n"<<"I win box "<<i;
        else if(who_wins_box[i]==2)
            cout<<"\n"<<"Enemy wins box "<<i;

    cout<<"\n\nB = "<<B<<"\nPush = "<<push<<endl;
    cout<<"\n\nBox count of 8 is "<<small_box_count[7]<<endl;

    print_board();
    create_file_for_push();

    return 0;
}


