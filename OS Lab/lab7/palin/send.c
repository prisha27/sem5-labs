#include <stdio.h>
#include <sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

struct my_msg{
	long int msg_type;
	int txt;
};



int main()
{
	//int n=1;
	struct my_msg msg;
	//char buf[100];
	int msgid = msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1)
	{
		printf("msgget failed\n");
		exit(1);
	}
	msg.msg_type=1;

	printf("enter value\n");
	scanf("%d", &msg.txt) ; 

    printf("done before sending type=%ld and txt=%d \n",msg.msg_type,msg.txt);
	if(msgsnd(msgid, &msg, sizeof(msg.txt),0)<0)
	{
		printf("error sending\n");
		exit(1);
	}

	printf("\nmessage sent :%d",msg.txt);
	return 0;

}