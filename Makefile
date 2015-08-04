CC = g++

all: dhsatest

dhsatest: network.o node.o keygroup.o onewayhash.o
	$(CC) -o dhsatest network.o node.o keygroup.o onewayhash.o main.cpp -lcrypto -lssl
onewayhash.o:
	$(CC) -c onewayhash.cpp -lcrypto -lssl
keygroup.o:
	 $(CC) -c keygroup.cpp
network.o:
	$(CC) -c network.cpp
node.o:
	$(CC) -c node.cpp
clean:
	$(RM) main *.o *~
