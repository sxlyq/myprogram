#include"myfifo.h"

char note[100];
pthread_mutex_t fifo_mutex;

void create_fifo(char *pathname,mode_t mode)
{
	pthread_mutex_init(&fifo_mutex,NULL);
	if(pthread_mutex_lock( &fifo_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if(mkfifo(pathname, mode) != 0)
		perror("failed to create the FIFO.");
	if(pthread_mutex_unlock( &fifo_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
}

void fifo_puts(char *info, FILE *fifo_fp)
{
	if(pthread_mutex_lock( &fifo_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if (fputs(info, fifo_fp ) == EOF)
    	{
      		fprintf( stderr, "Error writing data to fifo\n");
    	}
	if(pthread_mutex_unlock( &fifo_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
}

void remove_fifo(char *pathname)
{
	if(pthread_mutex_lock( &fifo_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if(remove(pathname) != 0)
		perror("failed to remove fifo.");
	if(pthread_mutex_unlock( &fifo_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
	if(pthread_mutex_destroy(&fifo_mutex) != 0)
		perror("An error occurred to pthread_mutex_destroy.\n");
}
