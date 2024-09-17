#include <sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

struct my_msg{
    long int msg_type;
  int txt;
};

int is_palin(int num)
{
    int og=num,rev=0,r;
    while(num!=0)
    {
      r=num%10;
      rev=rev*10+r;
      num /=10;
    }

    return(og==rev);
}

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

    if(msgrcv(msgid, &msg, sizeof(struct my_msg),1,0)<0)
    {
        printf("error receiving\n");
        exit(1);
    }

    if(is_palin(msg.txt))
        printf("The number is a palindrome");
    else
        printf("The number is not a palindrome");

    return 0;
}