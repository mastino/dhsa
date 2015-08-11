CC = g++

all: dhsatest

new:
	clear
	make clean
	make dhsatest

dhsatest: network.o node.o keygroup.o onewayhash.o aes.o dhmanager.o
	$(CC) -o dhsatest network.o node.o keygroup.o onewayhash.o aes.o dhmanager.o main.cpp -lcrypto -lssl
dhmanager.o:
	$(CC) -c dhmanager.cpp -lcrypto -lssl
aes.o:
	$(CC) -c aes.cpp -lcrypto -lssl
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
