CC = g++

all: dhsatest

dhsatest: network.o node.o keygroup.o onewayhash.o
	$(CC) -o dhsatest network.o node.o keygroup.o onewayhash.o main.cpp -lcrypto -lssl
onewayhash.o: onewayhash.h onewayhash.cpp
	$(CC) -c onewayhash.cpp -lcrypto -lssl
keygroup.o: keygroup.h keygroup.cpp onewayhash.o
	 $(CC) -c keygroup.cpp node.o onewayhash.o
network.o: network.h network.cpp node.o
	$(CC) -c network.cpp node.o
node.o: node.h node.cpp
	$(CC) -c node.cpp
clean:
	$(RM) main *.o *~
