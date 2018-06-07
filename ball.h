#ifndef BALL_H
#define BALL_H
#define def 5
using namespace std;

class ball{
private:
    int posX;
    int posY;
    int speed;
    char body='O';
public:
    const int _size=1;
    ball(){
        this->posX=0;
        this->posY=0;
        this->speed=def;
    }
    ball(const ball& v):posX(v.posX),posY(v.posY),speed(v.speed){};
    void setPosX(int x){
        this->posX=x;
    }

    void setPosY(int y){
        this->posY=y;
    }
    void setSpeed(int how){
        this->speed=how;
    }

    int getPosX(){
        return this->posX;
    }

    int getPosY(){
        return this->posY;
    }

    int getSpeed(){
        return this->speed;
    }

    char getBody(){
        return this->body;
    }

};
#endif // BALL_H
