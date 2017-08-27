gppflags= -Wall -pthread -std=c++17 -Ofast
hashfiles= ljus/hash/Hash.cpp ljus/hash/Hash.h
libraries= -lpistache -lyaml-cpp -largon2 -lsodium
cryptfiles= ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h

ljusa : main http.o hash.o config.o encryption.o

main : ljus.cpp ljus.h
	g++ $(gppflags) ljus.cpp ljus.h $(libraries) -o main

http.o : ljus/http/LjusHandler.cpp ljus/http/LjusHandler.h
	g++ $(gppflags) ljus/http/LjusHandler.cpp $(libraries)

hash.o : ljus/hash/Hash.cpp ljus/hash/Hash.h
	g++ $(gppflags) ljus/hash/Hash.cpp $(libraries)

config.o : config.h
	g++ $(gppflags) $(libraries) -o config.o

encryption.o : ljus/encryption/Crypt.cpp ljus/encryption/Crypt.h
	g++ $(gppflags) ljus/encryption/Crypt.cpp $(libraries)

clean:
	rm main http.o hash.o config.o encryption.o

test: test/test.cpp test/test.h
	g++ $(gppflags) test/test.cpp test/test.h test/catch.hpp $(hashfiles) $(cryptfiles) $(libraries) -o test.ex