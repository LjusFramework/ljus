NACL_INCLUDE=/usr/include/nacl
NACL_LIB=/usr/lib/nacl
CODEC_INCLUDE=/home/cents/ljus/includes/cppcodec/cppcodec
gppflags= -Wall -pthread -std=c++17 -Ofast
hashfiles= ljus/hash/Hash.cpp ljus/hash/Hash.h
libraries= -lpistache -lyaml-cpp -largon2 -I$(NACL_INCLUDE) -I$(CODEC_INCLUDE)
cryptfiles= ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h

ljusa : main 

main : ljus.cpp ljus.h
	g++ $(gppflags) ljus.cpp ljus.h $(libraries) $(hashfiles) $(cryptfiles) $(NACL_LIB)/randombytes.o $(NACL_LIB)/libnacl.a -o main

hash.o : ljus/hash/Hash.cpp ljus/hash/Hash.h
	g++ $(gppflags) ljus/hash/Hash.cpp Hash.h $(libraries)

config.o : config.h
	g++ $(gppflags) $(libraries) -o config.o

encryption.o : ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h
	g++ $(gppflags) ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h $(libraries)

clean:
	rm main http.o hash.o config.o encryption.o

test: test/test.cpp test/test.h
	g++ $(gppflags) test/test.cpp test/test.h test/catch.hpp $(hashfiles) $(cryptfiles) $(libraries) $(NACL_LIB)/randombytes.o $(NACL_LIB)/libnacl.a -o test.ex
