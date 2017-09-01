CC=g++
CFLAGS=-Wall -pthread -std=c++17 -Ofast
NACL_INCLUDE=/usr/include/nacl
NACL_LIB=/usr/lib/nacl

ROOT_DIR=${PWD}
gppflags= -Wall -pthread -std=c++17 -Ofast
hashfiles= ljus/hash/Hash.cpp ljus/hash/Hash.h
DEPENDENCIES= -lpistache -largon2 -I$(NACL_INCLUDE) $(NACL_LIB)/randombytes.o $(NACL_LIB)/libnacl.a
cryptfiles= ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h

ljusa : main 

main : ljus.cpp ljus.h
	$(CC) $(CFLAGS) ljus.cpp ljus.h $(DEPENDENCIES) hash.o crypt.o  -o main

test: test/test.cpp test/test.h hash.o crypt.o
	$(CC) $(CFLAGS) test/test.cpp test/test.h test/catch.hpp hash.o crypt.o $(DEPENDENCIES) -o tests.out

hash.o : ljus/hash/Hash.cpp
	$(CC) $(CFLAGS) -c ljus/hash/Hash.cpp -o hash.o $(DEPENDENCIES)

config.o : config.h
	$(CC) $(CFLAGS) $(libraries) -o config.o

crypt.o : ljus/encryption/Crypt.cpp
	$(CC) $(CFLAGS) -c ljus/encryption/Crypt.cpp $(DEPENDENCIES) -o crypt.o

clean:
	rm main crypt.o hash.o tests.out