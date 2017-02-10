CFLAGS = -Wall -Werror -c
LFLAGS = -Wall -Werror
CC = gcc
FOBJS = myfifo.o
TOBJS = tcpsocket.o
DOBJS = datamgr.o
SOBJS = sensor_db.o
SQLINK = -I/usr/include/mysql -lmysqlclient
LINK = -pthread -llist

EXE = server



all: $(OBJS) main.o
	$(CC) $(LFLAGS) $(FOBJS) $(TOBJS) $(DOBJS) $(SOBJS) main.o -o $(EXE) $(SQLINK) $(LINK)

myfifo.o: myfifo.h myfifo.c
	$(CC) $(CFLAGS) myfifo.c

datamgr.o: datamgr.h datamgr.c
	$(CC) $(CFLAGS) datamgr.c -D SET_MIN_TEMP=10 -D SET_MAX_TEMP=20

sensor_db.o: sensor_db.h config.h sensor_db.c
	$(CC) $(CFLAGS) sensor_db.c $(SQLINK)

tcpsocket.o: tcpsocket.h tcpsocket.c
	$(CC) $(CFLAGS) tcpsocket.c

main.o: list.h myqueue.h myfifo.h datamgr.h sensor_db.h main.c
	$(CC) $(CFLAGS) main.c -D SET_TIMEOUT=300 $(SQLINK) 


