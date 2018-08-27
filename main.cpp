#include <iostream>
#include <ctype.h>
#include "playarea.h"
#include "game.h"
#include <time.h>
#include <thread>
#include <curses.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include "session.h"
#include <mutex>
#include <chrono>
using namespace std;
#define PORT 28960


bool isEnd=false;

game* g;//=new game();
session* sesh;//=new session(g);
int server_fd, new_socket,sock, valread;

int opt =1;
int buff[11]={};
mutex game_mutex;
mutex g2;
void emptyBuff(){
  for(int i=0; i<11; i++){
    buff[i]=NULL;
  }
}
int _kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

void t_move1(){
  char ch;
  while(isEnd!=true)

  {

      //g->print_game();

      if(_kbhit())
      {
        game_mutex.lock();
          ch=getch();



          if(ch=='w')
          {

              g->movePlayer1Up();
              //g->print_game();

          }
          else if(ch=='s')

          {

              g->movePlayer1Down();
              //g->print_game();

          }
          game_mutex.unlock();
          this_thread::sleep_for (std::chrono::milliseconds(1));
      }

  }
}
void t_move2(){
  char ch;
  while(isEnd!=true)

  {

    //g->print_game();

      if(_kbhit())
      {
          game_mutex.lock();
          ch=getch();

          if(ch=='8')
          {

              g->movePlayer2Up();

          }
          else if(ch=='5')

          {

              g->movePlayer2Down();

          }
          game_mutex.unlock();

      }

      this_thread::sleep_for (std::chrono::milliseconds(1));
  }
}
//session controller

  void t_inet_send(){
    while(isEnd!=true){
    game_mutex.lock();
    sesh->setCurrent(g);
    sesh->preparePacketServer(buff);
    send(new_socket , &buff , sizeof(buff),MSG_CONFIRM);
    emptyBuff();
    valread=read(new_socket,&buff , sizeof(buff));
    if(valread==-1)cout<<"NAPAKA VALREAD"<<endl;
    sesh->setCurrent(g);
    sesh->openPacketServer(buff);
    g=sesh->getCurrent();
    emptyBuff();
    game_mutex.unlock();
    this_thread::sleep_for (std::chrono::milliseconds(1));

  }
}

  void t_inet_send_client(){
   while(isEnd!=true){
    game_mutex.lock();
    emptyBuff();
    sesh->setCurrent(g);
    //cout<<"vreu"<<endl;
    sesh->preparePacketClient(buff);
    //cout<<"vreu"<<endl;
    if(send(sock , &buff , sizeof(buff),MSG_CONFIRM) == -1){
      perror("napaka!");
      exit(-3500);
    }
    valread=read(sock,&buff , sizeof(buff));
    //cout<<"v clientuA"<<endl;
    sesh->setCurrent(g);
    //cout<<"v clientuB"<<endl;
    sesh->openPacketClient(buff);
    //cout<<"v clientuC"<<endl;
    g=sesh->getCurrent();
    emptyBuff();
    game_mutex.unlock();
    this_thread::sleep_for (std::chrono::milliseconds(1));
  }
  }
int x=1,y=1,z=0;
void t_main()
{
  //cout<<"tmain"<<endl;
    while(1)
    {
      if(g->getP1()->getScore()==5 || g->getP2()->getScore()==5){
        cout << endl << "konec igre" << endl;
        break;
      }

      game_mutex.lock();
        if(z==1 || z==2)
        {

            x= rand() % 1 + (-1);

            y= rand() % 1 + (-1);

            z=0;

            g->setSpeed(2000);

            g->spawnBall();


        }

        else
        {
            g->moveBall(x,y,z);
            g->print_game();
            //cout<<"moveBall"<<x<<" "<<y<<" "<<z<<endl;
            usleep(1000000);

        }
          game_mutex.unlock();
          this_thread::sleep_for (std::chrono::milliseconds(1));
      /*  thread tt(t_inet_send);
        thread tg(t_inet_get);
        tt.join();
        tg.join();*/
    }
    isEnd=true;

}
void t_main_c(){
  while(!isEnd){
    if(g->getP1()->getScore()==5 || g->getP2()->getScore()==5){
      cout << endl << "konec igre" << endl;
      break;
    }
    game_mutex.lock();
    //cout<<"a"<<g->getZoga()->getPosX()<<endl;
    g->print_game();
    game_mutex.unlock();
    this_thread::sleep_for (std::chrono::milliseconds(1));
  }
}



int main()

{
	string ip;
    clear();
	cout<<"Server: 1"<<endl << "Client: 2" << endl;
	char cha;
	cin>>cha;
	switch(cha){
		case '1':
    {
        cout<<"tu";
        struct sockaddr_in address;
        cout<<"tu";
        int addrlen = sizeof(address);
        cout<<"tu";

        if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
			{
				perror("setsockopt");
				exit(EXIT_FAILURE);
			}
		    address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons( PORT );

		if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
		{
			perror("bind failed");
			exit(EXIT_FAILURE);
		}

  cout<<"Waiting for client.."<<endl;
	if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    cout<<"Client connected!"<<endl;


    initscr();
    cbreak();
    noecho();
    g=new game();
    sesh=new session(g);

    g->print_game();

    g->addPlayersToArena();

    g->spawnBall();

    g->print_game();


    thread t1(t_main);
    thread t4(t_move1);
    thread t2(t_inet_send);
    //thread t3(t_inet_get);
    //while(1) g->print_game();

    t1.join();
    t2.join();
    //t3.join();
    t4.join();

			break;
		}
    case '2':{
      //printw("\nVnesi IP naslov streznika: ");
      cout<<"Vnesi IP :"<<endl;
      cin>>ip;
      struct sockaddr_in address;
      struct sockaddr_in serv_addr;
      //char *hello = "Hello from client";
      if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
      {
        cout << "\n Socket creation error \n";
        return -1;
      }

      memset(&serv_addr, '0', sizeof(serv_addr));

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(PORT);

      const char *c = ip.c_str();

      // Convert IPv4 and IPv6 addresses from text to binary form
      if(inet_pton(AF_INET, c, &serv_addr.sin_addr)<=0)
      {
        cout << "\nInvalid address/ Address not supported \n";
        return -1;
      }

      if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        cout << "\nConnection Failed \n";
        return -1;
      }

      initscr();
      cbreak();
      noecho();
      g=new game();
      g->spawnBall();
      g->addPlayersToArena();
      g->print_game();
      sesh=new session(g);
      //thread t2(t_inet_get_client);
    thread t0(t_main_c);
    thread t1(t_move2);
    thread t3(t_inet_send_client);


    t0.join();
    t1.join();
    //t2.join();
    t3.join();

    }
    case '3':
      break;
  }

    exit(0);

    return 0;

}
