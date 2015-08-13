CC = g++

all: dhsatest

new:
	clear
	make clean
	make dhsatest

dhsatest: network.o node.o keygroup.o onewayhash.o aes.o dhmanager.o tree_node.o leaf_node.o middle_node.o
	$(CC) -o dhsatest network.o node.o keygroup.o onewayhash.o aes.o dhmanager.o tree_node.o leaf_node.o middle_node.o main.cpp -lcrypto -lssl
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
tree_node.o:
	$(CC) -c tree_node.cpp
leaf_node.o:
	$(CC) -c leaf_node.cpp
middle_node.o:
	$(CC) -c middle_node.cpp
clean:
	$(RM) main *.o *~
