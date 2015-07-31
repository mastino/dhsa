CC = g++

all: dhsatest

dhsatest: node.o
	$(CC) -o dhsatest node.o main.cpp -lcrypto -lssl
node.o: node.h node.cpp
	$(CC) -c node.cpp -lcrypto -lssl

clean:
	$(RM) main *.o *~
