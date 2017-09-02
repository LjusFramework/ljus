CC=g++
CFLAGS=-Wall -pthread -std=c++1z -Ofast
NACL_INCLUDE=/usr/include/nacl
NACL_LIB=/usr/lib/nacl

ROOT_DIR=${PWD}
DEPENDENCIES= -lstdc++fs -lpistache -largon2 -I$(NACL_INCLUDE) $(NACL_LIB)/randombytes.o $(NACL_LIB)/libnacl.a

ljusa : main 

benchmark: benchmark/benchpress.hpp benchmark/base.cpp benchmark/cxxopts.hpp crypt.o hash.o files.o
	$(CC) $(CFLAGS) benchmark/benchpress.hpp benchmark/base.cpp build/crypt.o build/hash.o build/files.o $(DEPENDENCIES) -o benchmarker

main : ljus.cpp ljus.h
	$(CC) $(CFLAGS) ljus.cpp ljus.h build/hash.o build/crypt.o  $(DEPENDENCIES) -o main

test: test/test.cpp hash.o crypt.o files.o
	$(CC) $(CFLAGS) test/test.cpp test/test.h test/catch.hpp build/hash.o build/crypt.o build/files.o $(DEPENDENCIES) -o tests.out

hash.o : ljus/hash/Hash.cpp
	$(CC) $(CFLAGS) -c ljus/hash/Hash.cpp -o build/hash.o $(DEPENDENCIES)

config.o : config.h
	$(CC) $(CFLAGS) -c config.h -o build/config.o

files.o : ljus/files/Filesystem.h
	$(CC) $(CFLAGS) -c ljus/files/Filesystem.cpp -o build/files.o

crypt.o : ljus/encryption/Crypt.cpp config.o
	$(CC) $(CFLAGS) -c ljus/encryption/Crypt.cpp build/config.o $(DEPENDENCIES) -o build/crypt.o

clean:
	rm main *.o *.out *.gcno