#ifndef PLAYAREA_H
#define PLAYAREA_H
#include <curses.h>
#include <iostream>
using namespace std;
class playarea
{
private:
    int height;
    int width;
    char area[1000][1000];
public:
    playarea()
    {
        height=20;
        width=60;
        //area[height][width];
    }
    playarea(int h, int w):height(h),width(w)
    {
    }

    playarea(const playarea& v):height(v.height),width(v.width){
    for(int i=0; i<1000; i++){
        area[i][i]=v.area[i][i];
    }
    };

    void setHeight(int h)
    {
        this->height=h;
    }
    void setWidth(int w)
    {
        this->width=w;
    }
    int getWidth() {
        return this->width;
    }
    int getHeight() {
        return this->height;
    }
    char getArea(int y, int x)
    {
        return this->area[x][y];
    }

    void addToArea(int y, int x,char nekaj){
    this->area[y][x]=nekaj;
    }

    void setArea()
    {
        for(int x=0; x<height; x++)
        {
            if(x!=0 && x!=height-1)
            {
                for(int i=0; i<width; i++)
                {
                    area[x][i]=' ';

                }
            }
            else
            {
                for(int i=0; i<width; i++)
                {
                    area[x][i]='*';
                }
            }
        }
    }
    void printArea(){
		initscr();
    for(int i=0; i<height; i++){
		move(i, 25);
            //cout<<i<<" ";
            //printw("%i ",i);
            //if(i<10) printw(" ");//cout<<" ";
            //cout<<":";
            //printw(":");
        for(int j=0; j<width; j++){
            //cout<<area[i][j];
            printw("%c",area[i][j]);
        }
        //cout<<endl;
        printw("\n");
    }
    }
};

#endif //PLAYAREA_H
