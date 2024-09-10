#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t p;
	char *msg;
	int n;

	printf("Forking\n");
	p=fork();

	switch(p)
	{
		case -1:
			perror("error");
			break;

		case 0:
			msg="child";
			n=2;
			break;
		default:
			msg="parent";
			n=3;
			break;
	}
	for(;n>0;n--)
	{
		puts(msg);
		sleep(1);
	}
	exit(0);
}
