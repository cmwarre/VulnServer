
CC = gcc
CFLAGS = -c -fno-stack-protector
EXENAME = ../VulnServer
OBJECTS = main.o VulnCommand.o VulnConfig.o VulnLog.o VulnSocket.o VulnFunction.o VulnUtility.o

all: VulnServer

VulnServer: $(OBJECTS: .o = .cpp)
	    gcc -o $(EXENAME) $(OBJECTS) 

main.o: main.c
	$(CC) $(CFLAGS) main.c

VulnCommand.o: VulnCommand.c
	$(CC) $(CFLAGS) VulnCommand.c

VulnConfig.o: VulnConfig.c
	$(CC) $(CFLAGS) VulnConfig.c

VulnLog.o: VulnLog.c
	$(CC) $(CFLAGS) VulnLog.c

VulnSocket.o: VulnSocket.c
	$(CC) $(CFLAGS) VulnSocket.c

VulnUtility.o: VulnUtility.c
	$(CC) $(CFLAGS) VulnUtility.c
	
VulnFunction.o: VulnFunction.c
	$(CC) $(CFLAGS) VulnFunction.c

clean:
	rm -rf *.o
