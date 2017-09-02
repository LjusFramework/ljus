CC=g++
CFLAGS=-Wall -pthread -std=c++1z -Ofast
NACL_INCLUDE=/usr/include/nacl
NACL_LIB=/usr/lib/nacl

ROOT_DIR=${PWD}
DEPENDENCIES= -lstdc++fs -lpistache -largon2 -I$(NACL_INCLUDE) $(NACL_LIB)/randombytes.o $(NACL_LIB)/libnacl.a

ljusa : main 

main : ljus.cpp ljus.h
	$(CC) $(CFLAGS) ljus.cpp ljus.h $(DEPENDENCIES) hash.o crypt.o  -o main

test: test/test.cpp hash.o crypt.o files.o
	$(CC) $(CFLAGS) test/test.cpp test/test.h test/catch.hpp hash.o crypt.o files.o $(DEPENDENCIES) -o tests.out

hash.o : ljus/hash/Hash.cpp
	$(CC) $(CFLAGS) -c ljus/hash/Hash.cpp -o hash.o $(DEPENDENCIES)

config.o : config.h
	$(CC) $(CFLAGS) -c config.h -o config.o

files.o : ljus/files/Filesystem.h
	$(CC) $(CFLAGS) -c ljus/files/Filesystem.cpp -o files.o

crypt.o : ljus/encryption/Crypt.cpp config.o
	$(CC) $(CFLAGS) -c ljus/encryption/Crypt.cpp config.o $(DEPENDENCIES) -o crypt.o

clean:
	rm main *.o *.out