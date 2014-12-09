#include "stdlib.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include "termios.h"
#include "sstream"
#include "fstream"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/time.h"

using namespace std;
struct timeval myStruct;
long oldTime = 0;
long newTime = oldTime;

void transmit(string ident, int command1, int command2)
{
	// Initialize termios for serial transmission
	const char *device = "/dev/ttyO2";
	int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1)
	{
		printf( "failed to open port\n" );
	}

	struct termios options;
	tcgetattr(fd, &options);
	cfsetispeed(&options, B9600); //set baud rate in
	cfsetospeed(&options, B9600); //set baud rate out
	tcsetattr(fd, TCSANOW, &options); //do it now

	//convert data to appropriate form for transmission
	char happyData[14];
	sprintf(happyData, "%2s%6d,%6d\n",ident.c_str(),command1,command2);

	cout << happyData;
	close(fd);
}

int main(int argc, char **argv)
{
    int x1,y1,B;//,x2,y2,du,dd,dl,dr,backButton,guideButton,startButton,TL,TR,A,B,X,Y,LB,RB,LT,RT;
    int x1_old = 0;
    int y1_old = 0;
    int B_old = 0;//,x2_old,y2_old,du_old,dd_old,dl_old,dr_old,backButton_old,guideButton_old,startButton_old,TL_old,TR_old,A_old,B_old,X_old,Y_old,LB_old,RB_old,LT_old,RT_old;
    string commandInput;

    while(getline(cin,commandInput))
    {
	gettimeofday(&myStruct,NULL);
        newTime = (myStruct.tv_sec % 1000000) * 1000 + myStruct.tv_usec/1000;
    string xCheck = commandInput.substr(0,2);

    if (xCheck == "X1")
    {
        x1 = atoi(commandInput.substr(3,6).c_str());
        y1 = atoi(commandInput.substr(13,6).c_str());
//        x2 = atoi(commandInput.substr(24,6).c_str());
//        y2 = atoi(commandInput.substr(34,6).c_str());
//        du = atoi(commandInput.substr(45,1).c_str());
//        dd = atoi(commandInput.substr(50,1).c_str());
//        dl = atoi(commandInput.substr(55,1).c_str());
//        dr = atoi(commandInput.substr(60,1).c_str());
//        backButton = atoi(commandInput.substr(68,1).c_str());
//        guideButton = atoi(commandInput.substr(76,1).c_str());
//        startButton = atoi(commandInput.substr(84,1).c_str());
//        TL = atoi(commandInput.substr(90,1).c_str());
//        TR = atoi(commandInput.substr(95,1).c_str());
//        A = atoi(commandInput.substr(100,1).c_str());
        B = atoi(commandInput.substr(104,1).c_str());
//        X = atoi(commandInput.substr(108,1).c_str());
//        Y = atoi(commandInput.substr(112,1).c_str());
//        LB = atoi(commandInput.substr(118,1).c_str());
//        RB = atoi(commandInput.substr(123,1).c_str());
//        LT = atoi(commandInput.substr(129,3).c_str());
//        RT = atoi(commandInput.substr(136,3).c_str());
        // uncomment to print all values to stdout
        //printf("X1: %d Y1: %d X2: %d Y2: %d du: %d dd: %d dl: %d dr: %d back: %d guide: %d start: %d tl: %d tr: %d a: %d b: %d x: %d y: %d lb: %d rb: %d lt: %d rt: %d \n", x1,y1,x2,y2,du,dd,dl,dr,backButton,guideButton,startButton,TL,TR,A,B,X,Y,LB,RB,LT,RT);


        if (newTime - oldTime > 50)
        {
	oldTime = newTime;
	transmit("joy1",x1,y1);
        }
      }
    }
}
