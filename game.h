#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "playarea.h"
#include "player.h"
#include "ball.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
using namespace std;

class game
{

private:
    bool isEnd;
    player* p1;
    player* p2;
    playarea* arena;
    ball* zoga;
    int speed;
public:
    game()
    {
        isEnd=false;
        arena=new playarea(24,60);
        arena->setArea();
        p1=new player();
        p2=new player();
        zoga=new ball();
        speed=500;
    }
    game(const game& v):isEnd(v.isEnd),p1(v.p1),p2(v.p2),arena(v.arena),zoga(v.zoga),speed(v.speed) {};
    ~game();
    void setSpeed(int s)
    {
        this->speed=s;
    }
    int getSpeed(){
      return this->speed;
    }
    ball* getZoga(){
      return this->zoga;
    }
    player* getP1()
    {
        return this->p1;
    }
    player* getP2()
    {
        return this->p2;
    }
    void setP1(player* p){
      this->p1=p;
    }
    void setP2(player* p){
      this->p2=p;
    }
    void incrSpeed()
    {
        this->speed-=10;
    }
    void spawnBall()
    {
        arena->addToArea((arena->getHeight()/2),(arena->getWidth()/2),zoga->getBody());
        zoga->setPosX(arena->getWidth()/2);
        zoga->setPosY(arena->getHeight()/2);
    }
    void addPlayersToArena()
    {
        int i;
        for(i=0; i<p2->_size; i++)
        {
            arena->addToArea((arena->getHeight()/2)+i,0,p1->getBody(i));
            arena->addToArea((arena->getHeight()/2)+i,arena->getWidth()-1,p2->getBody(i));
        }
        p1->setBotPos((arena->getHeight()/2)+i-1);
        p1->setTopPos((arena->getHeight()/2));
        p2->setBotPos((arena->getHeight()/2)+i-1);
        p2->setTopPos((arena->getHeight()/2));
        //bottom > top oz lahko pa�
    }
    void movePlayer1Up()
    {
        int temp=p1->getBotPos(); //9
        int tempU=p1->getTopPos(); //6
        int x=0;
        int j=0;
        if(tempU!=1)
        {
            while(x<p2->_size)
            {
                arena->addToArea(tempU+x,0,' ');
                x++;
            }


            for(j; j<p2->_size; j++)
            {
                arena->addToArea(((tempU+j)-1),0,p1->getBody(j));
            }
            p1->setBotPos(temp-1);
            p1->setTopPos(tempU-1);
        }
    }
    void movePlayer1Down()
    {
        int temp=p1->getBotPos(); //9
        int tempU=p1->getTopPos(); //6
        int x=0;
        int j=0;
        if(temp!=this->arena->getHeight()-2)
        {
            while(x<p2->_size)
            {
                arena->addToArea(tempU+x,0,' ');
                x++;
            }
            for(j; j<p2->_size; j++)
            {
                arena->addToArea(((tempU+j)+1),0,p1->getBody(j));
            }
            p1->setBotPos(temp+1);
            p1->setTopPos(tempU+1);
        }
    }

    void movePlayer2Up()
    {
        int temp=p2->getBotPos(); //9
        int tempU=p2->getTopPos(); //6
        int x=0;
        int j=0;
        if(tempU!=1)
        {
            while(x<p2->_size)
            {
                arena->addToArea(tempU+x,arena->getWidth()-1,' ');
                x++;
            }


            for(j; j<p2->_size; j++)
            {
                arena->addToArea(((tempU+j)-1),arena->getWidth()-1,p2->getBody(j));
            }
            p2->setBotPos(temp-1);
            p2->setTopPos(tempU-1);
        }
    }
    void movePlayer2Down()
    {
        int temp=p2->getBotPos(); //9
        int tempU=p2->getTopPos(); //6
        int x=0;
        int j=0;
        if(temp!=this->arena->getHeight()-2)
        {
            while(x<p2->_size)
            {
                arena->addToArea(tempU+x,arena->getWidth()-1,' ');
                x++;
            }
            for(j; j<p2->_size; j++)
            {
                arena->addToArea(((tempU+j)+1),arena->getWidth()-1,p2->getBody(j));
            }
            p2->setBotPos(temp+1);
            p2->setTopPos(tempU+1);
        }
    }
    void moveBallClient(int x, int y)
    {
        int cur_x=zoga->getPosX();
        int cur_y=zoga->getPosY();

        if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y>0 && cur_y+y<arena->getHeight()-2)
        {

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y==arena->getHeight()-2)
        {
            y=-1;

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y==0)
        {
            y=1;

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(((p1->getTopPos()==cur_y+y) && (cur_x+x==1)) || ((p1->getTopPos()+1==cur_y+y) && (cur_x+x==1)))
        {
            x=1;
            if(y==1)
                y=-1;
            else
                y=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p1->getBotPos()==cur_y+y) && (cur_x+x==1)) || ((p1->getBotPos()-1==cur_y+y) && (cur_x+x==1)))
        {
            x=1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if((p1->getTopPos()+2==cur_y+y)&&(cur_x+x==1))
        {
            y=0;
            x=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getTopPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getTopPos()+1==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==1)
                y=-1;
            else
                y=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getBotPos()-1==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if((p2->getTopPos()+2==cur_y+y)&&(cur_x+x==arena->getWidth()-1))
        {
            y=0;
            x=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());

            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(cur_x+x>=arena->getWidth()-1)
        {
			flash();
            arena->addToArea(cur_y,cur_x,' ');
          /*  arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
			usleep(100000);
			zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
            arena->addToArea(cur_y+y,cur_x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,zoga->getBody());
            zoga->setPosX(cur_x+x+x);
            zoga->setPosY(cur_y+y+y);
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            usleep(100000);*/
             spawnBall();

        }
        else if(cur_x+x<=1)
        {

            flash();
            arena->addToArea(cur_y,cur_x,' ');
            //arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
          /*  usleep(100000);
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
            arena->addToArea(cur_y+y,cur_x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,zoga->getBody());
            zoga->setPosX(cur_x+x+x);
            zoga->setPosY(cur_y+y+y);
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            usleep(1000000);*/
           spawnBall();

        }


    }

    void moveBall(int &x, int &y, int &kdo)
    {
        int cur_x=zoga->getPosX();
        int cur_y=zoga->getPosY();

        if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y>0 && cur_y+y<arena->getHeight()-2)
        {

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y==arena->getHeight()-2)
        {
            y=-1;

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(cur_x+x>1 && cur_x+x<(arena->getWidth()-1) && cur_y+y==0)
        {
            y=1;

            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(((p1->getTopPos()==cur_y+y) && (cur_x+x==1)) || ((p1->getTopPos()+1==cur_y+y) && (cur_x+x==1)))
        {
            x=1;
            if(y==1)
                y=-1;
            else
                y=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p1->getBotPos()==cur_y+y) && (cur_x+x==1)) || ((p1->getBotPos()-1==cur_y+y) && (cur_x+x==1)))
        {
            x=1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if((p1->getTopPos()+2==cur_y+y)&&(cur_x+x==1))
        {
            y=0;
            x=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getTopPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getTopPos()+1==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==1)
                y=-1;
            else
                y=1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getBotPos()-1==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if(((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)) || ((p2->getBotPos()==cur_y+y) && (cur_x+x==arena->getWidth()-1)))
        {
            x=-1;
            if(y==-1)
                y=1;
            else
                y=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }

        else if((p2->getTopPos()+2==cur_y+y)&&(cur_x+x==arena->getWidth()-1))
        {
            y=0;
            x=-1;
            incrSpeed();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());

            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
        }
        else if(cur_x+x>=arena->getWidth()-1)
        {
			flash();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
			usleep(100000);
			zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
            arena->addToArea(cur_y+y,cur_x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,zoga->getBody());
            zoga->setPosX(cur_x+x+x);
            zoga->setPosY(cur_y+y+y);
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            usleep(100000);
            p1->addOne();

            kdo=1;

        }
        else if(cur_x+x<=1)
        {

            flash();
            arena->addToArea(cur_y,cur_x,' ');
            arena->addToArea(cur_y+y,cur_x+x,zoga->getBody());
            usleep(100000);
            zoga->setPosX(cur_x+x);
            zoga->setPosY(cur_y+y);
            arena->addToArea(cur_y+y,cur_x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            arena->addToArea(cur_y+y+y,cur_x+x+x,zoga->getBody());
            zoga->setPosX(cur_x+x+x);
            zoga->setPosY(cur_y+y+y);
            arena->addToArea(cur_y+y+y,cur_x+x+x,' ');
            usleep(1000000);
            p2->addOne();
            kdo=2;

        }


    }
    playarea* getArena()
    {
        return this->arena;
    }
    void print_game()
    {
		move(0,0);

        for(int i=0; i<(arena->getWidth()/2)-2; i++)
        {
            printw(" ");
        }
        //cout<<p1->getScore()<<" | "<<p2->getScore()<<endl;
        printw("%i | %i\n",p1->getScore(), p2->getScore());

        arena->printArea();
        //cout<<"Player 1: Top"<<p1->getTopPos()<<"  Bot"<<p1->getBotPos()<<"\nPlayer 2: Top"<<p2->getTopPos()<<"  Bot"<<p2->getBotPos()<<"\nBall: X"<<zoga->getPosX()<<"  Y"<<zoga->getPosY()<<endl;
		move(45,45);
		printw("Player 1 score: %i\nPlayer 2 score: %i \n",p1->getScore(), p2->getScore());
		refresh();
		}



};

#endif
