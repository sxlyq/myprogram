#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include <signal.h>
#include "myfifo.h"

#define FIFO_NAME 	"logFifo"
#define MAX 		100

int seq_num = 0;
FILE *fifo_fp;
FILE *fp;

void sighandler(int sig)
{
	signal(SIGINT,sighandler);
	fclose(fifo_fp);
	fclose(fp);
	if(remove(FIFO_NAME) != 0)
		perror("failed to remove fifo.");
	
	exit(0);
}


int main(void)
{
	char RD_buf[MAX];
	char WR_buf[MAX+50];
	time_t timestamp;
	/* Create the FIFO if it does not exist */
	create_fifo(FIFO_NAME, 0666);
	fifo_fp = fopen(FIFO_NAME, "r");
	fp = fopen("gateway.log", "w");
	signal(SIGINT,sighandler);
	while(1)
	{
		if(fgets(RD_buf,MAX,fifo_fp) != NULL)
		{
			seq_num++;
			time(&timestamp);
			sprintf(WR_buf,"%d %s %s",seq_num,ctime(&timestamp),RD_buf);
			fputs(WR_buf,fp);
		}
	}
	return 0;
}
