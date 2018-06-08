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
using namespace std;



bool isEnd=false;

game* g;
int server_fd, new_socket, valread;
struct sockaddr_in_address;
int opt =1;
char buff='0';


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
	
	}
int main()

{
	string ip, port;
    clear();

    //initscr();

    //cbreak();

   //noecho();
	//printw("1...Server\n2...Client\n3...Local\nchoice:");
	cout<<"YES ESE "<<endl;
	char cha;
	cin>>cha;
	switch(cha){
		case '1':{

		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
			{
				perror("setsockopt");
				exit(EXIT_FAILURE);
			}
		    address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons( port );
		
		if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
		{
			perror("bind failed");
			exit(EXIT_FAILURE);
		}
		
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
    thread t2(t_inet);
			
			break;
		}
		case '2':
			//printw("\nVnesi IP naslov streznika: ");
			cout<<"Vnesi IP :"<<endl;
			cin>>ip;
			//printw("Vnesi port: ");
			cout<<"Vnesi Port:"<<endl;
			cin>>port;
			break;
		case '3':
			break;
		}



    srand(time(NULL));









    int a;

    //cin>>a;

    /*

        int ch;

        do{

            ch=_getch();

        }

        while(ch!='w');

        cout<<"yes";

        */
	initscr();
	cbreak();
	noecho();
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

    endwin();

    return 0;

}

