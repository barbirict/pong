#ifndef SESSION_H
#define SESSION_H
#define packet_end "33113/c"
#include "game.h"
using namespace std;

class session{

private:
    game* current;
    bool running;
    bool win;
public:
    session(game* cur){
      current=cur;
    }

    void preparePacketServer(int packet[11]){
      packet[0]=current->getZoga()->getPosX();
      packet[1]=current->getZoga()->getPosY();
      packet[2]=current->getSpeed();
      packet[3]=current->getP1()->getTopPos();
      packet[4]=current->getP1()->getBotPos();
      packet[6]=current->getP1()->getScore();
      packet[7]=current->getP2()->getScore();
      //packet[8]=99;
      packet[10]=33113;
      //return packet;
    }
    void openPacketServer(int packet[11]){
      //cout<<"server odpira paket"<<endl;

      int temp=current->getP2()->getBotPos(); //9
      int tempU=current->getP2()->getTopPos(); //6
      //if(packet[3]==3612){
        //cout<<"PREJET PAKET"<<packet[3]<<endl;
        //cout<<"it does"<<endl;
      if(packet[0]<tempU){
        current->movePlayer2Up();

      //  cout<<"if true!";
      }
      else if(packet[0]>tempU ) current->movePlayer2Down();
      //packet={};
    //}
  }
    void preparePacketClient(int packet[11]){
      packet[0]=current->getP2()->getTopPos();
      packet[1]=current->getP2()->getBotPos();
      packet[3]=3612;

    }
    void openPacketClient(int packet[11]){
      //int temp=(int)packet[0];
      int cur_x=current->getZoga()->getPosX();
      int cur_y=current->getZoga()->getPosY();
      int temp=current->getP1()->getBotPos(); //9
      int tempU=current->getP1()->getTopPos(); //6
    int razlikaX=packet[0]-cur_x;
    int razlikaY=packet[1]-cur_y;
      current->moveBallClient(razlikaX,razlikaY);
    /*  current->getArena()->addToArea(cur_y,cur_x,' ');
      current->getArena()->addToArea(packet[1],packet[0],current->getZoga()->getBody());
      current->getZoga()->setPosX(packet[0]);
      current->getZoga()->setPosY(packet[1]);
      current->setSpeed(packet[2]);
      */if(packet[3]>tempU && packet[4]>temp) current->movePlayer1Down();
      else if(packet[3]<tempU && packet[4]<temp)current->movePlayer1Up();
      //current->getP1()->setTopPos(packet[3]);
      //current->getP1()->setBotPos(packet[4]);
      current->getP1()->setScore(packet[6]);
      current->getP2()->setScore(packet[7]);
      //packet={};
    }
    game* getCurrent(){
      return current;
    }
    void setCurrent(game* cur){
      current=cur;
    }


};
#endif // SESSION_H
