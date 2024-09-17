#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

struct my_msg{
    long int msg_type;
    char txt[100];
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

    if(msgrcv(msgid, &msg, sizeof(msg.txt),1,0)<0)
    {
        printf("error receiving\n");
    }
    printf("\nmessage  :%s",msg.txt);
    return 0;
}
