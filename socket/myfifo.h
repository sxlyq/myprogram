#ifndef MYFIFO_H_
#define MYFIFO_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

void create_fifo(char *pathname,mode_t mode);

void fifo_puts(char *info, FILE *fifo_fp);

void remove_fifo(char *pathname);

#endif
