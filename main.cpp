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
using namespace std;
#define PORT 28960


bool isEnd=false;

game* g;
int server_fd, new_socket, valread;

int opt =1;
char buff[100]={};


int _kbhit()
{

    static const int STDIN = 0;

    static bool initialized = false;



    if (! initialized)
    {

        // Use termios to turn off line buffering

        termios term;

        tcgetattr(STDIN, &term);

        term.c_lflag &= ~ICANON;

        tcsetattr(STDIN, TCSANOW, &term);

        setbuf(stdin, NULL);

        initialized = true;

    }

    int bytesWaiting;

    ioctl(STDIN, FIONREAD, &bytesWaiting);

    return bytesWaiting;

}

void t_main()
{



    int x=0,y=0,z=0;

    x= rand() % 1 + (-1);

    y= rand() % 1 + (-1);

    while(g->getP1()->getScore()<5 && g->getP2()->getScore()<5)
    {

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

            usleep(300000);

        }

    }
    isEnd=true;

}


void t_inet(){

    while(!isEnd){
      valread=read(new_socket,buff,1);
       if(buff[0]=='8')

      {

          //cout<<"gor";

          g->movePlayer2Up();

      }

      else if(buff[0]=='5')

      {

          //cout<<"dol";

          g->movePlayer2Down();

      }
      g->print_game();
    }
	}

  void t_inet_client(){

  }
int main()

{
	string ip;
    clear();

    //initscr();

    //cbreak();

   //noecho();
	//printw("1...Server\n2...Client\n3...Local\nchoice:");
	cout<<"YES ESE "<<endl;
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

        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
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
    cout<<"Client connected!"<<endl;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    cout<<"yes";
    thread t2(t_inet);


    initscr();
    cbreak();
    noecho();
    g=new game();

    g->print_game();

    g->addPlayersToArena();

    g->spawnBall();

    g->print_game();

    thread t1(t_main);

    char ch;

    bool running=true;

    while(running)

    {
        g->print_game();

        if(_kbhit())
        {
            ch=getch();

            if(isEnd==true)
                t1.join();
                t2.join();

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

        }



    }

    endwin();
			break;
		}
    case '2':{
            //printw("\nVnesi IP naslov streznika: ");
            cout<<"Vnesi IP :"<<endl;
            cin>>ip;
            //printw("Vnesi port: ");
            /*cout<<"Vnesi Port:"<<endl;
            cin>>port;*/
      struct sockaddr_in address;
      int sock = 0, valread;
      struct sockaddr_in serv_addr;
      //char *hello = "Hello from client";
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
      /*send(sock , hello , strlen(hello) , 0 );
      valread = read( sock , buffer, 1024);
      printf("Hello message sent\n");
      printf("%s\n",buffer );*/

      initscr();
      cbreak();
      noecho();
      g=new game();

      g->print_game();

      g->addPlayersToArena();

      g->spawnBall();

      g->print_game();

      thread t1(t_main);

      char ch;

      bool running;
      running=true;

      while(running)

      {
          g->print_game();

          if(_kbhit())
          {
              ch=getch();

              if(isEnd==true)
                  t1.join();

              if(ch=='8')

              {
                buff[0]='8';
                  send(sock , buff , strlen(buff) , 0 );
                  cout<<"gor";

                  g->movePlayer1Up();

              }

              else if(ch=='5')

              {
                buff[0]='5';
                  send(sock , buff , strlen(buff) , 0 );
                  cout<<"dol";

                  g->movePlayer1Down();

              }

          }

            break;
    }
  }
		case '3':
			break;
		}

    return 0;

}
