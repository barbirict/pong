#include <iostream>
#include <conio.h>
#include <ctype.h>
#include "playarea.h"
#include "game.h"
#include <time.h>
#include <thread>
#include <windows.h>
using namespace std;

bool isContact=false;
game* g;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void t_main(){

    int i=0;
    int x=0,y=0,z=0;
    x= rand() % 1 + (-1);
    y= rand() % 1 + (-1);
    while(g->getP1()->getScore()<5 || g->getP2()->getScore()<5){
    if(z==1 || z==2){
        x= rand() % 1 + (-1);
        y= rand() % 1 + (-1);
        z=0;
        g->setSpeed(2000);
        g->spawnBall();

    }
    else{
    g->moveBall(x,y,z);
    Sleep(g->getSpeed());
    }
    }
    }

int main()
{
    cout<<"start";
    srand(time(NULL));
    ShowConsoleCursor(false);

    int a;
    cin>>a;
/*
    int ch;
    do{
        ch=_getch();
    }
    while(ch!='w');
    cout<<"yes";
    */
    g=new game();
    g->print_game();
    g->addPlayersToArena();
    g->spawnBall();
    g->print_game();

    thread t1(t_main);
    char ch, ch2;
    bool running=true;
    while(running)
    {
        g->print_game();
        if(_kbhit()){
         ch=_getch();
        if(isContact==true)t1.join();
        if(ch=='w')
        {
            cout<<"gor";
            g->movePlayer1Up();
        }
        else if(ch=='s')
        {
            cout<<"dol";
            g->movePlayer1Down();
        }
        else if(ch=='8')
        {
            cout<<"gor";
            g->movePlayer2Up();
        }
        else if(ch=='5')
        {
            cout<<"dol";
            g->movePlayer2Down();
        }
        }
    }
    return 0;
}
